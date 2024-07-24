/**
 * 插入排序是改进的冒泡排序：纸牌摸牌
 * 冒泡是和未排序的区域比较选一个最大, 如果刚好式排好序的O(n^2) 退化为 O(n)
 * 插入式和已排序的区域比较选一个区域插入，如果刚好式排好序的O(n^2) 退化为 O(n)
 *
 * 插入排序通常比冒泡法排序要性能好，因为如果刚好比最大值还大或者比最小值还小就不用比，而冒泡法因为都是无序区域所以必须每个都比较
 */

(() => {
    function sort(arr, len) {
        let tmp;
        for (let i = 1; i < len; i++) {
            for (let j = i - 1; j >= 0 && arr[j] > arr[j + 1]; j -= 1) {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }

    // 构造数据
    let arr = [];
    for (let i = 0; i < 1000000; i++) {
        //arr.push(i);
        //arr.push(10000 - i - 1);
        arr.push(Number.parseInt(Math.random() * 10000));
    }

    let start = new Date().getTime();
    sort(arr, arr.length);
    let end = new Date().getTime();
    console.log(arr);
    console.log("%c 花费时间" + (end - start) + "ms", 'color:#000652;');
})();