//達成 http requests 的函式簡化
function http_get(url) {
    const httpRequest = new XMLHttpRequest();

    httpRequest.open("GET", url, false);
    httpRequest.setRequestHeader('Content-type', 'application/ecmascript');
    httpRequest.setRequestHeader('Access-Control-Allow-Origin', '*');
    httpRequest.send();

    return httpRequest.responseText
}