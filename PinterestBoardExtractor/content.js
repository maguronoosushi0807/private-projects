(async () => {

    const urls = new Set();

    const sleep = (ms) => {
        return new Promise(resolve => setTimeout(resolve, ms));
    };

    let currentScroll = 0;

    const SCROLL_STEP = 1000;

    const MAX_SCROLLS = 100;

    let lastHeight = 0;

    // Pinterest画像URLを高画質化
    const convertToOriginal = (url) => {

        return url.replace(
            /\/(236x|474x|564x|736x)\//,
            "/originals/"
        );

    };

    for (let i = 0; i < MAX_SCROLLS; i++) {

        console.log(`Scroll ${i + 1}`);

        const images = document.querySelectorAll("img");

        images.forEach(img => {

            let bestUrl = null;

            // srcset優先
            if (img.srcset) {

                const candidates = img.srcset
                    .split(",")
                    .map(item => item.trim().split(" ")[0]);

                if (candidates.length > 0) {

                    bestUrl = candidates[candidates.length - 1];

                }
            }

            // fallback
            if (!bestUrl && img.src) {

                bestUrl = img.src;

            }

            if (!bestUrl) return;

            if (!bestUrl.includes("pinimg.com")) return;

            // 高画質化
            bestUrl = convertToOriginal(bestUrl);

            urls.add(bestUrl);

        });

        console.log(`Collected: ${urls.size}`);

        currentScroll += SCROLL_STEP;

        window.scrollTo({
            top: currentScroll,
            behavior: "smooth"
        });

        await sleep(1500);

        const newHeight = document.body.scrollHeight;

        if (
            newHeight === lastHeight &&
            currentScroll + window.innerHeight >= newHeight
        ) {

            console.log("Reached end");

            break;
        }

        lastHeight = newHeight;
    }

    console.log("Finished");
    console.log([...urls]);

    return [...urls];

})();