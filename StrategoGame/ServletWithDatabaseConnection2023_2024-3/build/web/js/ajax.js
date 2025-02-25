
function createTableFromJSON(data) {
    var html = "<table><tr><th>Category</th><th>Value</th></tr>";
    for (const x in data) {
        var category = x;
        var value = data[x];
        html += "<tr><td>" + category + "</td><td>" + value + "</td></tr>";
    }
    html += "</table>";
    return html;
}

function displayUserInfo(userData) {
    var html = "<form id='editForm' onsubmit='editUser();return false;'>";
    for (const x in userData) {
        var category = x;
        var value = userData[x];
        html += "<label for='" + category + "'>" + category + ":</label><br>";
        html += "<input type='text' id='" + category + "' name='" + category + "' value='" + value + "' required><br>";
    }
    html += "<input type='hidden' name='action' value='edit'>";
    html += "<input type='submit' class='button' value='Save'>";
    html += "</form>";
    $("#ajaxContent").html(html);
}

function editUser() {
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
        if (xhr.readyState === 4 && xhr.status === 200) {
            $("#ajaxContent").html("User information updated successfully");
        } else if (xhr.status !== 200) {
            $("#ajaxContent").html("Error updating user information");
        }
    };
    var data = $('#editForm').serialize();
    xhr.open('POST', 'LoginServlet');
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send(data);
}

function getUser() {
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
        if (xhr.readyState === 4 && xhr.status === 200) {
            displayUserInfo(JSON.parse(xhr.responseText));
        } else if (xhr.status !== 200) {
            $("#ajaxContent").html("User not exists or incorrect password");
        }
    };
    var data = $('#loginForm').serialize();
    xhr.open('GET', 'GetKeeper?' + data);
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();
}

function initDB() {
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
        if (xhr.readyState === 4 && xhr.status === 200) {
            $("#ajaxContent").html("Successful Initialization");
        } else if (xhr.status !== 200) {
            $("#ajaxContent").html("Error Occurred");
        }
    };

    xhr.open('GET', 'InitDB');
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();
}

function deleteDB() {
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
        if (xhr.readyState === 4 && xhr.status === 200) {
            $("#ajaxContent").html("Successful Deletion");
        } else if (xhr.status !== 200) {
            $("#ajaxContent").html("Error Occurred");
        }
    };

    xhr.open('GET', 'DeleteDB');
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();
}
function showEditForm() {
    var editFormContainer = document.getElementById("editFormContainer");
    editFormContainer.innerHTML = ""; // Clear previous content
    editFormContainer.style.display = "block";

    // Populate the edit form with user data (replace 'userData' with actual data)
    editFormContainer.innerHTML = `
                <form id='editForm' onsubmit='editUser();return false;'>
                    <label for='username'>Username:</label><br>
                    <input type='text' id='username' name='username' value='[currentUsername]' readonly><br>
                    <!-- Other fields -->
                    <label for='email'>Email:</label><br>
                    <input type='text' id='email' name='email' value='[currentEmail]' readonly><br>
                    <!-- Other fields -->
                    <input type='hidden' name='action' value='edit'>
                    <input type='submit' class='button' value='Save'>
                </form>
            `;
}