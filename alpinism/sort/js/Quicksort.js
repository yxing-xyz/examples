// 迭代 -- 改进引入三数取中基准
(() => {
  function sort(arr, leftIndex, rightIndex) {
    //定义cutoff
    const cutoff = 10;
    // 长度小于等于10进行冒泡排序
    if (rightIndex < cutoff) {
      //冒泡排序
      let index = rightIndex;
      let remeber = 0;
      let tmp;
      while (index > 0) {
        for (let i = 0; i < index; i++) {
          if (arr[i] > arr[i + 1]) {
            remeber = i;
            tmp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = tmp;
          }
        }
        index = remeber;
        remeber = 0;
      }
      return;
    }

    //定义栈
    let stack = [];
    stack.push({
      leftIndex: leftIndex,
      rightIndex: rightIndex,
    });

    let node, midIndex;
    while (stack.length !== 0) {
      node = stack.pop();
      leftIndex = node.leftIndex;
      rightIndex = node.rightIndex;
      //三数取中,左边横取中间数做privot
      midIndex = (leftIndex + rightIndex > 1) + 1;
      if (arr[leftIndex] > arr[midIndex]) {
        [arr[leftIndex], arr[midIndex]] = [arr[midIndex], arr[leftIndex]];
      }
      if (arr[midIndex] > arr[rightIndex]) {
        [arr[midIndex], arr[rightIndex]] = [arr[rightIndex], arr[midIndex]];
      }
      if (arr[leftIndex] < arr[midIndex]) {
        [arr[leftIndex], arr[midIndex]] = [arr[midIndex], arr[leftIndex]];
      }
      let privotValue = arr[leftIndex];
      let flagIndex = leftIndex + 1;
      // 分区
      for (let j = leftIndex + 1; j <= rightIndex; j++) {
        if (arr[j] < privotValue) {
          [arr[flagIndex], arr[j]] = [arr[j], arr[flagIndex]];
          flagIndex++;
        }
      }
      flagIndex--;
      [arr[leftIndex], arr[flagIndex]] = [arr[flagIndex], arr[leftIndex]];

      if (leftIndex < flagIndex - 1) {
        stack.push({
          leftIndex: leftIndex,
          rightIndex: flagIndex - 1,
        });
      }
      if (flagIndex + 1 < rightIndex) {
        stack.push({
          leftIndex: flagIndex + 1,
          rightIndex,
        });
      }
    }
  }

  let arr = [];
  let len = 10**7;
  for (let i = 0; i < len; i += 1) {
    arr.push(Number.parseInt(Math.random() * len));
  }

  let start = new Date().getTime();
  sort(arr, 0, arr.length - 1);
  let end = new Date().getTime();

  console.log("%c 花费时间" + (end - start) + "ms", "color:#000652;");
})();
