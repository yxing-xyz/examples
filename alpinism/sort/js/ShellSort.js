// 希尔排序
(() => {
    function sort(arr, len) {
        let tmp,
            gap = len;

        while ((gap >>= 1) > 0) {
            for (let i = gap; i < len; i++) {
                for (let j = i - gap; j >= 0 && arr[j] > arr[j + gap]; j -= gap) {
                    tmp = arr[j];
                    arr[j] = arr[j + gap];
                    arr[j + gap] = tmp;
                }
            }
        }
    }


    // 构造数据
    let arr = [];
    for (let i = 0; i < 10000; i += 1) {
        //arr.push(i);
        //arr.push(10 - i - 1);
        arr.push(Number.parseInt(Math.random() * 10000));
    }
    let start = new Date().getTime();
    sort(arr, arr.length);
    let end = new Date().getTime();

    console.log("%c 花费时间" + (end - start) + "ms", 'color:#000652;');
})();