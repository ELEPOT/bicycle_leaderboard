function http_get(url) {
    const httpRequest = new XMLHttpRequest();

    httpRequest.open("GET", url, false);
    httpRequest.setRequestHeader('Content-type', 'application/ecmascript');
    httpRequest.setRequestHeader('Access-Control-Allow-Origin', '*');
    httpRequest.send();

    return httpRequest.responseText
}

function http_get_async(url) {
    const httpRequest = new XMLHttpRequest();

    httpRequest.open("GET", url, true);
    httpRequest.setRequestHeader('Content-type', 'application/ecmascript');
    httpRequest.setRequestHeader('Access-Control-Allow-Origin', '*');
    httpRequest.send();
}

