document.addEventListener('DOMContentLoaded', () => {
    const themeIcons = {
        light: 'assets/img/night_icon.png', // Moon (switch to dark)
        dark: 'assets/img/light_icon.png'   // Sun (switch to light)
    };
    const btn = document.getElementById('themeToggleBtn');
    const icon = document.getElementById('themeIcon');
    function setTheme(theme) {
        document.documentElement.setAttribute('data-bs-theme', theme);
        localStorage.setItem('bs-theme', theme);
        icon.src = themeIcons[theme];
        icon.alt = theme === 'dark' ? 'Light mode icon' : 'Dark mode icon';
        btn.classList.remove('bg-light', 'bg-dark');
        btn.classList.add(theme === 'dark' ? 'bg-light' : 'bg-dark');
    }
    setTheme(localStorage.getItem('bs-theme') || 'dark');
    btn.addEventListener('click', () => setTheme(document.documentElement.getAttribute('data-bs-theme') === 'dark' ? 'light' : 'dark'));
});