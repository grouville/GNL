# gnl
<b>Simple implementation of the getline function in C.</b>

The aim of the project was to learn the use of static variables, and get familiar with the scope and longevity of variables and functions.

<ol>
<li>The function has no authorized library other than libft (my own), and the read function.</li>
<li>One of the challenge was the use of a variable sized buffer, which could be changed in the header.</li>
<li>We had to be sure of having no memory leaks, and to handle the variably sized buffer using the static array (read by blocs of 100, or 100k)</li>
</ol>
