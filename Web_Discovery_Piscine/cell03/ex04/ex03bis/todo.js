const listContainer = $('#ft_list');
$(() => { // Wrapping in a nameless function to ensure DOM is loaded.
    const saved = getCookie("todos");
    if (saved) {
        const todos = JSON.parse(saved);
        todos.forEach(todo => addTodo(todo));
    }
    $('#new-btn').on('click', () => {
        const text = prompt("Enter your new task:");
        if (text && text.trim() !== "") {
            addTodo(text.trim());
            saveTodos();
        }
    });
});
const addTodo = text => {
    const $div = $('<div>').addClass('todo-item');
    const $span = $('<span>').text(text);
    const $trash = $('<span>')
        .addClass('trash-icon')
        .attr('title', 'Delete')
        .html('<img src="https://img.icons8.com/?id=85081&format=png&color=ff0000" />')
        .on('click', e => {
            e.stopPropagation();
            if (confirm("Do you want to delete this task?")) {
                $div.remove();
                saveTodos();
            }
        });
    $div.append($span, $trash);
    listContainer.append($div);
};
const saveTodos = () => {
    const todos = [];
    listContainer.find('.todo-item').each((_, item) => {
        todos.push($(item).find('span').first().text());
    });
    document.cookie = "todos=" + JSON.stringify(todos) + "; path=/; max-age=31536000"; // 1 year
};
const getCookie = name => {
    const cookies = document.cookie.split('; ');
    for (let cookie of cookies) {
        const [k, v] = cookie.split('=');
        if (k === name) return decodeURIComponent(v);
    }
    return null;
};