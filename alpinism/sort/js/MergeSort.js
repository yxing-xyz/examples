(() => {
  function merge(arr, low, mid, hight) {
    let k = 0,
      left_low = low,
      right_low = mid + 1,
      tmp = [];

    while (left_low <= mid && right_low <= hight) {
      if (arr[left_low] < arr[right_low]) {
        tmp[k++] = arr[left_low++]
      } else {
        tmp[k++] = arr[right_low++]
      }
    }

    if (left_low <= mid) {
      // 右边有剩余
      for (let i = left_low; i <= mid; i++) {
        tmp[k++] = arr[i];
      }
    }

    if (right_low <= hight) {
      // 左边有剩余
      for (let i = right_low; i <= hight; i++) {
        tmp[k++] = arr[i];
      }
    }

    // tmp复制给arr
    for (i = 0; i < hight - low + 1; i++)
      arr[low + i] = tmp[i];
    //console.log(arr, low, mid, hight);
  }

  function sort(arr, start, end) {
    let mid = 0;
    if (start < end) {
      mid = (start + end) >> 1;
      sort(arr, start, mid);
      sort(arr, mid + 1, end);
      merge(arr, start, mid, end);
    }
  }

  // 构造数据
  let arr = [];
  for (let i = 0; i < 10000000; i += 1) {
    //arr.push(10000 - i - 1);
    arr.push(Number.parseInt(Math.random() * 10000000));
  }
  let start = new Date().getTime();
  sort(arr, 0, arr.length - 1);
  console.log(arr);
  let end = new Date().getTime();
  console.log("%c 花费时间" + (end - start) + "ms", 'color:#000652;');
})();