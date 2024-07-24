;;打印变量类型
(defun variable-type (var)
      (cond ((null var) 'null)
            ((listp var) 'list)
            ((numberp var) 'number)
            ((stringp var) 'string)
            ((symbolp var) 'symbol)
            ((functionp var) 'function)
            ((vectorp var) 'vector)
            ((hash-table-p var) 'hash-table)
            ((bufferp var) 'buffer)
            ((windowp var) 'window)
            ((framep var) 'frame)
            ((processp var) 'process)
            ((eq var t) 't)
            (t 'unknown)))


;;批量加入lsp工作区
(let ((dirs '("/home/x/workspace/tencent/sec-gateway/src/gateway/statsvr"
               "/home/x/workspace/tencent/sec-gateway/src/console/svr")))
   (dolist (elem dirs)
     (lsp-workspace-folders-add elem)))