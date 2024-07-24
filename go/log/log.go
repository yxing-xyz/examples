package log

import (
	"errors"
	"fmt"
	"os"
	"path/filepath"
	"sort"
	"strings"
	"sync"
	"time"
)

const backupTimeFormat = "2006010215"

type LoginLoger struct {
	FileName   string // 日志文件名
	MaxBackups int    // 最大保留日志数量
	path       string // 当前最大的写入日志数量
	file       *os.File
	mu         sync.Mutex

	millCh    chan bool
	startMill sync.Once
}

func (l *LoginLoger) Write(p []byte) (n int, err error) {
	l.mu.Lock()
	defer l.mu.Unlock()
	if l.path == "" {
		// 第一次运行
		if err = l.open(l.fileNameByTime(time.Now())); err != nil {
			return 0, err
		}
	}

	if l.path != l.fileNameByTime(time.Now()) {
		// 需要轮转文件
		if err := l.rotate(); err != nil {
			return 0, err
		}
	}

	return l.file.Write(p)
}

func (l *LoginLoger) close() error {
	if l.file == nil {
		return nil
	}
	err := l.file.Close()
	l.file = nil
	return err
}

func (l *LoginLoger) rotate() error {
	if err := l.close(); err != nil {
		return err
	}
	if err := l.open(l.fileNameByTime(time.Now())); err != nil {
		return err
	}
	return nil
}

func (l *LoginLoger) open(path string) error {
	err := os.MkdirAll(l.dir(), 0755)
	if err != nil {
		return fmt.Errorf("can't make directories for new logfile: %s", err)
	}

	f, err := os.OpenFile(path, os.O_CREATE|os.O_APPEND|os.O_WRONLY, os.FileMode(0600))
	if err != nil {
		return fmt.Errorf("can't open new logfile: %s", err)
	}
	l.file = f
	l.path = path
	l.mill()
	return nil
}

func (l *LoginLoger) fileNameByTime(t time.Time) string {
	prefix, ext := l.prefixAndExt()
	timestamp := t.Format(backupTimeFormat)
	return filepath.Join(l.dir(), fmt.Sprintf("%s%s%s", prefix, timestamp, ext))
}

func (l *LoginLoger) dir() string {
	return filepath.Dir(l.FileName)
}

func (l *LoginLoger) prefixAndExt() (string, string) {
	var filename = filepath.Base(l.FileName)
	var ext = filepath.Ext(filename)
	var prefix = filename[:len(filename)-len(ext)] + "."
	return prefix, ext
}

func (l *LoginLoger) mill() {
	l.startMill.Do(func() {
		l.millCh = make(chan bool, 1)
		go l.millRun()
	})
	select {
	case l.millCh <- true:
	default:
	}
}

func (l *LoginLoger) millRun() {
	for range l.millCh {
		// what am I going to do, log this?
		_ = l.clean()
	}
}

// 清除多余的日志文件
func (l *LoginLoger) clean() error {
	files, err := l.oldLogFiles()
	if err != nil {
		return err
	}
	if len(files) <= l.MaxBackups {
		return nil
	}
	remove := files[l.MaxBackups:]
	for _, v := range remove {
		if err := os.Remove(filepath.Join(l.dir(), v.Name())); err != nil {
			return err
		}
	}
	return nil
}

type logInfo struct {
	timestamp time.Time
	os.FileInfo
}

func (l *LoginLoger) oldLogFiles() ([]logInfo, error) {
	files, err := os.ReadDir(l.dir())
	if err != nil {
		return nil, fmt.Errorf("can't read log file directory: %s", err)
	}
	logFiles := []logInfo{}

	prefix, ext := l.prefixAndExt()

	for _, f := range files {
		if f.IsDir() {
			continue
		}
		if t, err := l.timeFromName(f.Name(), prefix, ext); err == nil {
			fileInfo, err := f.Info()
			if err != nil {
				fmt.Println(err)
				continue
			}
			logFiles = append(logFiles, logInfo{t, fileInfo})
		}
	}

	sort.Sort(byFormatTime(logFiles))

	return logFiles, nil
}

func (l *LoginLoger) timeFromName(filename, prefix, ext string) (time.Time, error) {
	if !strings.HasPrefix(filename, prefix) {
		return time.Time{}, errors.New("mismatched prefix")
	}
	if !strings.HasSuffix(filename, ext) {
		return time.Time{}, errors.New("mismatched extension")
	}
	ts := filename[len(prefix) : len(filename)-len(ext)]
	return time.Parse(backupTimeFormat, ts)
}

type byFormatTime []logInfo

func (b byFormatTime) Less(i, j int) bool {
	return b[i].timestamp.After(b[j].timestamp)
}

func (b byFormatTime) Swap(i, j int) {
	b[i], b[j] = b[j], b[i]
}

func (b byFormatTime) Len() int {
	return len(b)
}
