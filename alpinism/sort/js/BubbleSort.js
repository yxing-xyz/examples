/*
    这个只优化了有序系列,还可以优化比较已排序序列见golagn实现.
*/
(() => {
    function sort(arr, len) {
        for (let i = 0; i < len - 1; i++) {
            let didSwap = false; //改进如果有序直接0(n)
            for (let j = 0; j < len - 1 - i; j++) {
                if (arr[j] > arr[j + 1]) {
                    didSwap = true;
                    let swap = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = swap;
                }
            }
            if (didSwap == false) {
                break;
            }
        }
        return arr;
    }

    // 构造数据
    let arr = [];
    for (let i = 0; i < 10000; i++) {
        //arr.push(i);
        //arr.push(10000 - i - 1);
        arr.push(Number.parseInt(Math.random() * 10000));
    }

    let start = new Date().getTime();
    sort(arr, arr.length);
    let end = new Date().getTime();
    console.log("%c 花费时间" + (end - start) + "ms", 'color:#000652;');
    // 完成运行次数：sn = 1/2*n^2 - 1/2*n" (n属于正整数);
})();