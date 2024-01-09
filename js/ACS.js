function getXMLHttpRequest() {
    var xmlhttp = null;
    if (window.XMLHttpRequest) {
        xmlhttp = new XMLHttpRequest();
    }
    else {
        xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
    }
    return xmlhttp;
}

function create() {
    var user = document.getElementById("NameC").value;
    var pwd = document.getElementById("PwdC").value;
    var repwd = document.getElementById("RePwdC").value;
    var url = "/cgi-bin/create.cgi?" + user + ":" + pwd + ":" + repwd;
    var xmlhttp = getXMLHttpRequest();
    xmlhttp.onreadystatechange = function () {
        if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
            if (xmlhttp.responseText == "ok") {
                window.location.href = "login.html";
            }
            else {
                document.getElementById("NameC").value = '';
                document.getElementById("PwdC").value = '';
                document.getElementById("RePwdC").value = '';
            }
        }
    }
    xmlhttp.open("GET", url, true);
    xmlhttp.setRequestHeader("If-Modified-Since", "0");
    xmlhttp.send();
}

function login() {
    var user = document.getElementById("Name").value;
    var pwd = document.getElementById("Pwd").value;
    var url = "/cgi-bin/login.cgi?" + user + ":" + pwd;
    var xmlhttp = getXMLHttpRequest();
    xmlhttp.onreadystatechange = function () {
        if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
            if (xmlhttp.responseText == "ok") {
                window.location.href = "main.html";
            }
            else {
                alert("用户名或密码错误!");
                document.getElementById("Name").value = '';
                document.getElementById("Pwd").value = '';
            }
        }
    }
    xmlhttp.open("GET", url, true);
    xmlhttp.setRequestHeader("If-Modified-Since", "0");
    xmlhttp.send();
}

function add() {
    var addName = document.getElementById("addName").value;
    var addAddress = document.getElementById("addAddress").value;
    var addPhone = document.getElementById("addPhone").value;
    var url = "/cgi-bin/addUser.cgi?" + addName + ":" + addAddress + ":" + addPhone;
    var xmlhttp = getXMLHttpRequest();
    xmlhttp.onreadystatechange = function () {
        if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
            if (xmlhttp.responseText == "ok") {
                alert("添加成功");
                document.getElementById("addName").value = '';
                document.getElementById("addAddress").value = '';
                document.getElementById("addPhone").value = '';
            }
            else {
                document.getElementById("addName").value = '';
                document.getElementById("addAddress").value = '';
                document.getElementById("addPhone").value = '';
            }
        }
    }
    xmlhttp.open("GET", url, true);
    xmlhttp.setRequestHeader("If-Modified-Since", "0");
    xmlhttp.send();
}

function delete_ID() {
    var deleteID = document.getElementById("delete_id").value;
    if (deleteID == "") {
        alert("ID不可为空!");
    } else {
        var url = "/cgi-bin/deleteID.cgi?" + deleteID;
        var xmlhttp = getXMLHttpRequest();
        xmlhttp.onreadystatechange = function () {
            if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
                if (xmlhttp.responseText == "ok") {
                    alert("删除成功");
                    document.getElementById("delete_id").value = '';
                }
                else {
                    alert("此ID不存在!");
                    document.getElementById("delete_id").value = '';
                }
            }
        }
        xmlhttp.open("GET", url, true);
        xmlhttp.setRequestHeader("If-Modified-Since", "0");
        xmlhttp.send();
    }
}

function update_ID() {
    var update_id = document.getElementById("update_id").value;
    var updateName = document.getElementById("updateName").value;
    var updateAddr = document.getElementById("updateAddr").value;
    var updatePhone = document.getElementById("updatePhone").value;
    if (update_id == "" || updateName == "" || updateAddr == "" || updatePhone == "") {
        alert("请完善信息!");
    } else {
        var url = "/cgi-bin/updateID.cgi?" + update_id + ":" + updateName + ":" + updateAddr + ":" + updatePhone;
        var xmlhttp = getXMLHttpRequest();
        xmlhttp.onreadystatechange = function () {
            if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
                if (xmlhttp.responseText == "ok") {
                    alert("修改成功");
                    document.getElementById("update_id").value = '';
                    document.getElementById("updateName").value = '';
                    document.getElementById("updateAddr").value = '';
                    document.getElementById("updatePhone").value = '';
                }
                else {
                    alert("此ID不存在!");
                    document.getElementById("update_id").value = '';
                    document.getElementById("updateName").value = '';
                    document.getElementById("updateAddr").value = '';
                    document.getElementById("updatePhone").value = '';
                }
            }
        }
        xmlhttp.open("GET", url, true);
        xmlhttp.setRequestHeader("If-Modified-Since", "0");
        xmlhttp.send();
    }
}

function select_User() {
    var table = document.getElementById("UserTable");
    var rows = table.getElementsByTagName("tr");
    for (var n = rows.length - 1; n > 0; n--) {
        table.deleteRow(n);
    }
    var url = "/cgi-bin/selectUser.cgi?";
    var xmlhttp = getXMLHttpRequest();
    xmlhttp.onreadystatechange = function () {
        if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
            var data = xmlhttp.responseText;
            var values = data.split("  ");
            var sum = 0;
            var tb = document.createElement("tbody");
            tb.classList.add("bg-white", "divide-y", "dark:divide-gray-700", "dark:bg-gray-800");
            for (var j = 0; j < values.length / 4; j++) {
                var row = document.createElement("tr");
                row.classList.add("text-gray-700", "dark:text-gray-400");
                for (var i = 0; i < 4; i++) {
                    var cell = document.createElement("td");
                    cell.classList.add("px-4", "py-3");
                    cell.textContent = values[sum];
                    row.appendChild(cell);
                    sum++;
                }
                tb.appendChild(row);
            }
            table.appendChild(tb);
        }
    };
    xmlhttp.open("GET", url, true);
    xmlhttp.setRequestHeader("If-Modified-Since", "0");
    xmlhttp.send();
}

function access_records() {
    var table = document.getElementById("accessTable");
    var rows = table.getElementsByTagName("tr");
    for (var n = rows.length - 1; n > 0; n--) {
        table.deleteRow(n);
    }
    var url = "/cgi-bin/access_records.cgi?";
    var xmlhttp = getXMLHttpRequest();
    xmlhttp.onreadystatechange = function () {
        if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
            var data = xmlhttp.responseText;
            var values = data.split("  ");
            var sum = 0;
            var tb = document.createElement("tbody");
            tb.classList.add("bg-white", "divide-y", "dark:divide-gray-700", "dark:bg-gray-800");
            for (var j = 0; j < values.length / 5; j++) {
                var row = document.createElement("tr");
                row.classList.add("text-gray-700", "dark:text-gray-400");
                for (var i = 0; i < 5; i++) {
                    var cell = document.createElement("td");
                    cell.classList.add("px-4", "py-3");
                    cell.textContent = values[sum];
                    row.appendChild(cell);
                    sum++;
                }
                tb.appendChild(row);
            }
            table.appendChild(tb);
        }
    };
    xmlhttp.open("GET", url, true);
    xmlhttp.setRequestHeader("If-Modified-Since", "0");
    xmlhttp.send();
}

function trespassing() {
    var table = document.getElementById("trespassing");
    var rows = table.getElementsByTagName("tr");
    for (var n = rows.length - 1; n > 0; n--) {
        table.deleteRow(n);
    }
    var url = "/cgi-bin/trespassing.cgi?";
    var xmlhttp = getXMLHttpRequest();
    xmlhttp.onreadystatechange = function () {
        if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
            var data = xmlhttp.responseText;
            var values = data.split("  ");
            var sum = 0;
            var tb = document.createElement("tbody");
            tb.classList.add("bg-white", "divide-y", "dark:divide-gray-700", "dark:bg-gray-800");
            for (var j = 0; j < values.length / 2; j++) {
                var row = document.createElement("tr");
                row.classList.add("text-gray-700", "dark:text-gray-400");
                for (var i = 0; i < 2; i++) {
                    var cell = document.createElement("td");
                    cell.classList.add("px-4", "py-3");
                    cell.textContent = values[sum];
                    row.appendChild(cell);
                    sum++;
                }
                tb.appendChild(row);
            }
            table.appendChild(tb);
        }
    };
    xmlhttp.open("GET", url, true);
    xmlhttp.setRequestHeader("If-Modified-Since", "0");
    xmlhttp.send();
}

function select_msg(a) {
    var msg = document.getElementById("msg").value;
    if (msg == "") {
        alert("请输入信息!");
    } else {
        var table = document.getElementById("UserTable");
        var rows = table.getElementsByTagName("tr");
        for (var n = rows.length - 1; n > 0; n--) {
            table.deleteRow(n);
        }
        var url = "/cgi-bin/selectMsg.cgi?" + a + ":" + msg;
        var xmlhttp = getXMLHttpRequest();
        xmlhttp.onreadystatechange = function () {
            if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
                if (xmlhttp.responseText == "error") {
                    alert("无此msg!");
                } else {
                    var data = xmlhttp.responseText;
                    var values = data.split("  ");
                    var sum = 0;
                    var tb = document.createElement("tbody");
                    tb.classList.add("bg-white", "divide-y", "dark:divide-gray-700", "dark:bg-gray-800");
                    for (var j = 0; j < values.length / 4; j++) {
                        var row = document.createElement("tr");
                        row.classList.add("text-gray-700", "dark:text-gray-400");
                        for (var i = 0; i < 4; i++) {
                            var cell = document.createElement("td");
                            cell.classList.add("px-4", "py-3");
                            cell.textContent = values[sum];
                            row.appendChild(cell);
                            sum++;
                        }
                        tb.appendChild(row);
                    }
                    table.appendChild(tb);
                }
            }
        };
        xmlhttp.open("GET", url, true);
        xmlhttp.setRequestHeader("If-Modified-Since", "0");
        xmlhttp.send();
    }
}

function precisely(b) {
    var begintime = document.getElementById("begintime").value;
    var endtime = document.getElementById("endtime").value;
    var begintimes = document.getElementById("begintimes").value;
    var endtimes = document.getElementById("endtimes").value;
    if (begintime == "" || endtime == "" || begintimes == "" || endtimes == "") {
        alert("请输入起止时间!");
    } else {
        switch (b) {
            case 1:
                var table = document.getElementById("accessTable");
                var rows = table.getElementsByTagName("tr");
                for (var n = rows.length - 1; n > 0; n--) {
                    table.deleteRow(n);
                }
                break;

            case 2:
                var table = document.getElementById("trespassing");
                var rows = table.getElementsByTagName("tr");
                for (var n = rows.length - 1; n > 0; n--) {
                    table.deleteRow(n);
                }
                break;
        }
        var url = "/cgi-bin/precisely.cgi?" + b + "*" + begintime + "*" + begintimes + "*" + endtime + "*" + endtimes;
        var xmlhttp = getXMLHttpRequest();
        xmlhttp.onreadystatechange = function () {
            if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
                if (xmlhttp.responseText == "error") {
                    alert("此时间段内无记录!");
                } else {
                    var data = xmlhttp.responseText;
                    var values = data.split("  ");
                    var sum = 0;
                    var tb = document.createElement("tbody");
                    tb.classList.add("bg-white", "divide-y", "dark:divide-gray-700", "dark:bg-gray-800");
                    switch (b) {
                        case 1:
                            for (var j = 0; j < values.length / 5; j++) {
                                var row = document.createElement("tr");
                                row.classList.add("text-gray-700", "dark:text-gray-400");
                                for (var i = 0; i < 5; i++) {
                                    var cell = document.createElement("td");
                                    cell.classList.add("px-4", "py-3");
                                    cell.textContent = values[sum];
                                    row.appendChild(cell);
                                    sum++;
                                }
                                tb.appendChild(row);
                            }
                            table.appendChild(tb);
                            break;
                        case 2:
                            for (var j = 0; j < values.length / 2; j++) {
                                var row = document.createElement("tr");
                                row.classList.add("text-gray-700", "dark:text-gray-400");
                                for (var i = 0; i < 2; i++) {
                                    var cell = document.createElement("td");
                                    cell.classList.add("px-4", "py-3");
                                    cell.textContent = values[sum];
                                    row.appendChild(cell);
                                    sum++;
                                }
                                tb.appendChild(row);
                            }
                            table.appendChild(tb);
                            break;
                    }
                }
            }
        };
        xmlhttp.open("GET", url, true);
        xmlhttp.setRequestHeader("If-Modified-Since", "0");
        xmlhttp.send();
    }
}

function user_records() {
    var name = document.getElementById("name_records").value;
    if (name == "")
        alert("请输入信息!");
    else {
        var table = document.getElementById("accessTable");
        var rows = table.getElementsByTagName("tr");
        for (var n = rows.length - 1; n > 0; n--) {
            table.deleteRow(n);
        }
        var url = "/cgi-bin/name_records.cgi?" + name;
        var xmlhttp = getXMLHttpRequest();
        xmlhttp.onreadystatechange = function () {
            if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
                if (xmlhttp.responseText == "error") {
                    alert("无此用户记录!");
                } else {
                    var data = xmlhttp.responseText;
                    var values = data.split("  ");
                    var sum = 0;
                    var tb = document.createElement("tbody");
                    tb.classList.add("bg-white", "divide-y", "dark:divide-gray-700", "dark:bg-gray-800");
                    for (var j = 0; j < values.length / 5; j++) {
                        var row = document.createElement("tr");
                        row.classList.add("text-gray-700", "dark:text-gray-400");
                        for (var i = 0; i < 5; i++) {
                            var cell = document.createElement("td");
                            cell.classList.add("px-4", "py-3");
                            cell.textContent = values[sum];
                            row.appendChild(cell);
                            sum++;
                        }
                        tb.appendChild(row);
                    }
                    table.appendChild(tb);
                }
            }
        };
        xmlhttp.open("GET", url, true);
        xmlhttp.setRequestHeader("If-Modified-Since", "0");
        xmlhttp.send();
    }
}
