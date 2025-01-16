const form = document.querySelector("#register-form");
const passwordField = document.getElementById("password");
const confirmPasswordField = document.getElementById("confirm-password");
const errorMessage = document.createElement("p");

errorMessage.style.color = "red";
errorMessage.style.fontSize = "0.9em";
errorMessage.style.display = "none"; // Oculta a mensagem inicialmente
confirmPasswordField.parentNode.appendChild(errorMessage);

form.addEventListener("submit", (e) => {
    const password = passwordField.value;
    const confirmPassword = confirmPasswordField.value;

    if (password !== confirmPassword) {
        e.preventDefault();
        errorMessage.textContent = "As senhas não coincidem!";
        errorMessage.style.display = "block";
    } else {
        errorMessage.style.display = "none";
    }
});
