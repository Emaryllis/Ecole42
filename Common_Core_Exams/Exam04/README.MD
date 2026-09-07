<h1>Exam 4</h1>
<h3>Level 2 (vbc only)</h3>
<ol>
  <li>Modify given unexpected function to return 1 instead of void, delete all other functions, including main.</li>
  <li>Only accepts 2 params, return 1 if isn't 2.</li>
  <li>Syntax requirements:<ul>
    <li>Balanced braces:<ul>
      <li>Left +1, right -1</li>
      <li>Negative balance after add/subtract or current is <code>(</code> & next is <code>)</code> -> <code>return unexpected(')')</code></li>
    </ul></li>
     <li>Single digit int (Return <code>unexpected(next)</code> if invalid)</li>
  <li>If current is <code>+</code>, <code>*</code>, next can't be <code>+</code>, <code>*</code>, <code>)</code>, or <code>EOF</code> (Return <code>unexpected()</code> if invalid)</li>
  <code class="language-c">if (isdigit(c)) {
  if (n && isdigit(n))
      return unexpected(n);
} else if (c == '+' || c == '*') {
  if (n == '+' || n == '*' || n == ')' || n == '\0')
      return unexpected(n ? n : 0);
} else if (c != '(' && c != ')')
        return unexpected(c);</code>
  <li>If <code>b_bal > 0 or last is +, * or (</code> after loop, return <code>unexpected(0)</code></li>
  </ul></li>
  <li>Parse input using ft_sum</li>
  <li>If input str pointer leads to non null char (after ft_sum) = didn't process everything = invalid = return 1</li>
  <li><code>int ft_sum(char **s)</code><ol>
    <li>Initalize sum with ft_product</li>
    <li>Iterate when <code>current == +</code> while summing with ft_product</li>
    <li>Return sum after loop</li>
  </ol></li>
  <li><code>int ft_product(char **s)</code><ol>
    <li>Initalize num with ft_factor</li>
    <li>Iterate when <code>current == +, 0-9, ( </code></li>
    <li>Increment <code>*s</code> if <code>current == *</code></li>
    <li>Multiply num with ft_factor(s)</li>
    <li>Return num when loop ends</li></ol>
  <li><code>int ft_factor(char **s)</code><ol>
    <li>Initalize sum with ft_product</li>
    <li>If current is 0-9, return it & increment <code>*s</code></li>
    <li>If current is <code>(</code>, increment <code>*s</code>, store ft_sum's return as num, increment <code>*s</code>, return num</li>
    <li>Return 1 as base case (This shouldn't be possible to reach)</li></ol>
  <li>Print output of ft_sum & return 0</li>
</ol>
