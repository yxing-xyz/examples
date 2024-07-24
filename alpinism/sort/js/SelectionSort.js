// 选择排序
(() => {
    function sort(arr, len) {
        let index, tmp;
        for (let i = 0; i < len - 1; i++) {
            index = i;
            for (let j = i + 1; j < len; j++) {
                if (arr[j] < arr[index]) {
                    index = j;
                }
            }

            tmp = arr[i];
            arr[i] = arr[index];
            arr[index] = tmp;
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