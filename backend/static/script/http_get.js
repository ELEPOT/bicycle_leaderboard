function http_get(url) {
    httpRequest.open("GET", url, false);
    httpRequest.setRequestHeader('Content-type', 'application/ecmascript');
    httpRequest.setRequestHeader('Access-Control-Allow-Origin', '*');
    httpRequest.send();

    return httpRequest.responseText
}

