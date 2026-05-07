document.getElementById("extractButton").addEventListener("click", async () => {

    // 現在開いているタブ取得
    const [tab] = await chrome.tabs.query({
        active: true,
        currentWindow: true
    });

    // content.js 実行
    const results = await chrome.scripting.executeScript({
        target: { tabId: tab.id },
        files: ["content.js"]
    });

    // content.js の戻り値
    const urls = results[0].result;

    // 表示エリア
    const output = document.getElementById("output");

    output.innerHTML = "";

    urls.forEach(url => {

        const div = document.createElement("div");

        div.textContent = url;

        output.appendChild(div);

    });

});