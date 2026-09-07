const listContainer = document.getElementById('ft_list');
window.onload = () => {
	const saved = getCookie("todos");
	if (saved) {
		const todos = JSON.parse(saved);
		todos.forEach(todo => addTodo(todo));
	}
};
document.getElementById('new-btn').addEventListener('click', () => {
	const text = prompt("Enter your new task:");
	if (text && text.trim() !== "") {
		addTodo(text.trim());
		saveTodos();
	}
});
const addTodo = text => {
	const div = document.createElement('div');
	div.className = 'todo-item';
	const span = document.createElement('span');
	span.textContent = text;
	const trash = document.createElement('span');
	trash.innerHTML = '<img src="https://img.icons8.com/?id=85081&format=png&color=ff0000" />';
	trash.className = 'trash-icon';
	trash.title = 'Delete';
	trash.addEventListener('click', e => {
		e.stopPropagation();
		if (confirm("Do you want to delete this task?")) {
			div.remove();
			saveTodos();
		}
	});
	div.appendChild(span);
	div.appendChild(trash);
	listContainer.appendChild(div);
  }
  
const saveTodos = () => {
	const todos = [];
	const items = listContainer.querySelectorAll('.todo-item');
	items.forEach(item => todos.push(item.textContent));
	document.cookie = "todos=" + JSON.stringify(todos) + "; path=/; max-age=31536000"; // 1 year
}
const getCookie = name => {
	const cookies = document.cookie.split('; ');
	for (let cookie of cookies) {
		const [k, v] = cookie.split('=');
		if (k === name) return decodeURIComponent(v);
	}
	return null;
}
