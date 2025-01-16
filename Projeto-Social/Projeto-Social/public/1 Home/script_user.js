function createUserIcon(name) {
    const userIcon = document.getElementById("user-icon");

    const initials = name
        .split(" ")
        .map(word => word[0])
        .join("");

    userIcon.textContent = initials;
    userIcon.style.display = "flex"; 
}

function showLogout() {
    const logoutContainer = document.getElementById("logout-container");

    logoutContainer.style.display = 'block';

    setTimeout(function() {
        logoutContainer.style.opacity = 1;
        logoutContainer.style.transform = 'translateY(10px)'; 
    }, 10); 
}

async function displayUserName() {
    try {
        const response = await fetch("/user", { method: "GET" });
        const data = await response.json();

        if (data.success) {
            const userNameContainer = document.getElementById("user-name-container");
            const userNameElement = document.getElementById("user-name");

            userNameElement.textContent = data.name;  
            userNameContainer.style.display = "block";  
        } else {
            console.log('Erro ao carregar o nome do usuário: ', data.message);
        }
    } catch (error) {
        console.error('Erro ao acessar a rota /user:', error);
    }
}


window.onload = displayUserName;


async function checkUserLogin() {
    const response = await fetch("/user", { method: "GET" });
    const data = await response.json();

    const loginLinkContainer = document.getElementById("loginav");
    const userIcon = document.getElementById("user-icon");

    if (data.success) {
        loginLinkContainer.style.display = 'none';
        userIcon.style.display = 'flex'; 
        createUserIcon(data.name); 
        displayUserName(data.name);
    } else {
        loginLinkContainer.style.display = 'block';
        userIcon.style.display = 'none'; 
    }
}


window.onload = checkUserLogin;


window.onload = checkUserLogin;


async function logout() {
    await fetch("/logout", { method: "GET" });
    window.location.reload(); 
}


window.onload = checkUserLogin;
