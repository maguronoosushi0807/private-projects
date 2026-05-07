document.getElementById("extractButton").addEventListener("click", async () => {

    // 現在タブ取得
    const [tab] = await chrome.tabs.query({
        active: true,
        currentWindow: true
    });

    // content.js 実行
    const results = await chrome.scripting.executeScript({
        target: { tabId: tab.id },
        files: ["content.js"]
    });

    // URL一覧
    const urls = results[0].result;

    console.log(urls);

    // 表示
    const output = document.getElementById("output");

    output.innerHTML = `
        Found ${urls.length} images
    `;

    // txt化
    const text = urls.join("\n");

    // Blob生成
    const blob = new Blob(
        [text],
        { type: "text/plain" }
    );

    // Blob URL生成
    const blobUrl = URL.createObjectURL(blob);

    // ダウンロード
    const a = document.createElement("a");

    a.href = blobUrl;

    a.download = "pinterest_urls.txt";

    a.click();

    // メモリ解放
    URL.revokeObjectURL(blobUrl);

});