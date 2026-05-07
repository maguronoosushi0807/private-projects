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

    // URL一覧取得
    const urls = results[0].result;

    console.log(urls);

    // UI表示
    const output = document.getElementById("output");

    output.innerHTML = `
        Found ${urls.length} images<br>
        Downloading...
    `;

    // 順番にDL
    for (let i = 0; i < urls.length; i++) {

        const url = urls[i];

        console.log(`Downloading ${i + 1}`);

        try {

            // URLからファイル名生成
            const filename = getFileName(url, i);

            // ダウンロード
            await chrome.downloads.download({
                url: url,
                filename: `Pinterest/${filename}`,
                saveAs: false
            });

        } catch (err) {

            console.error(err);

        }
    }

    output.innerHTML += "<br>Finished";

});


// ファイル名生成
function getFileName(url, index) {

    try {

        const cleanUrl = url.split("?")[0];

        const parts = cleanUrl.split("/");

        const last = parts[parts.length - 1];

        if (last && last.includes(".")) {

            return `${index}_${last}`;

        }

    } catch (e) {}

    return `${index}.jpg`;

}