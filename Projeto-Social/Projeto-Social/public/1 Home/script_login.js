const loginForm = document.querySelector("#login-form");
const emailField = document.getElementById("email");
const passwordField = document.getElementById("password");
const errorMessage = document.createElement("p");

errorMessage.style.color = "red";
errorMessage.style.fontSize = "0.9em";
errorMessage.style.display = "none"; // Oculta a mensagem inicialmente
passwordField.parentNode.appendChild(errorMessage);

loginForm.addEventListener("submit", (e) => {
    const email = emailField.value.trim();
    const password = passwordField.value.trim();

    if (!email || !password) {
        e.preventDefault();
        errorMessage.textContent = "Por favor, preencha todos os campos!";
        errorMessage.style.display = "block";
    } else {
        errorMessage.style.display = "none";
    }
});
