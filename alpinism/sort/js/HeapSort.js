// 堆排序解决TOP K问题
// 大根堆排序举例: 1. 初始堆(父节点必须大于子节点的完全二叉树), 2. 根节点已经是最大的,可以剔除然后重新堆化选出下一个最大值

// 核心点: 
// 1. 绝对二叉树可以用数组模拟
// 2. length / 2 - 1 是最后一个非叶子节点索引, 因为完全二叉树的特性后面的节点都是非叶子节点所以循环堆化得到初始堆

(() => {
  function heapify(arr, parentIndex, lastIndex) {
    let indexValue = arr[parentIndex];
    let childIndex = 2 * parentIndex + 1;
    while (childIndex <= lastIndex) {
      if (
        childIndex + 1 <= lastIndex &&
        arr[childIndex] < arr[childIndex + 1]
      ) {
        childIndex += 1;
      }
      if (indexValue >= arr[childIndex]) break;
      arr[parentIndex] = arr[childIndex];
      parentIndex = childIndex;
      childIndex = 2 * parentIndex + 1;
    }
    arr[parentIndex] = indexValue;
  }
  function sort(arr) {
    for (let i = arr.length / 2 - 1; i >= 0; i--) {
      heapify(arr, i, arr.length - 1);
    }
    for (let i = 1; i <= arr.length - 1; i++) {
      let temp = arr[arr.length - i];
      arr[arr.length - i] = arr[0];
      arr[0] = temp;
      heapify(arr, 0, arr.length - i - 1);
    }
  }

  let arr = [];
  let len = 10 ** 7;
  for (let i = 0; i < len; i += 1) {
    arr.push(Number.parseInt(Math.random() * len));
  }
  // arr = [1, 3, 4, 5, 2, 6, 9, 7, 8, 0];

  let start = new Date().getTime();
  sort(arr);
  let end = new Date().getTime();
  console.log("%c 花费时间" + (end - start) + "ms", "color:#000652;");
})();
