// 控制台输出即将要打开的网页地址
(function(){
  // 获取所有的a标签
  const links = document.querySelectorAll('a');

  // 为每个a标签添加点击事件监听器
  links.forEach(link => {
    link.addEventListener('click', (event) => {
      console.log('a标签要打开的窗口网页：', link.href); // 在控制台输出要打开的窗口网页
      // event.preventDefault(); // 阻止a标签的默认行为（跳转到链接）
    });
  });


  const originalWindowOpen = window.open;
  // 重写 window.open 函数
  window.open = function (url, target, features) {
    console.log('window.open要打开的窗口网页：', url); // 在控制台输出要打开的窗口网页
    return originalWindowOpen.call(window, url, target, features); // 调用原始的 window.open 函数
  };
})()