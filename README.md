The Get Next Line (GNL) project at 42 School is a core C project that teaches you how to:

Read from a file descriptor line by line

Handle dynamic memory allocation

Manage multiple file descriptors simultaneously

Understand buffered input, static variables, and string manipulation

📖 Project Objective
You must implement the function:

c
Copy
Edit
char *get_next_line(int fd);
It should:

Return the next line from a file descriptor fd each time it’s called.

Work with any file or input stream (e.g. files, pipes, standard input).

Return:

A full line ending in \n, including the newline character.

The last line if it doesn't end with \n.

NULL when there’s nothing left to read or on error.

✅ Mandatory Rules
You must only use:
read, malloc, free, and your own functions (not strchr, strlen, etc.).

Handle buffers manually (read only once per call, up to BUFFER_SIZE bytes).

Must not leak memory.

Must return one line at a time (not the entire file at once).

Must work with multiple file descriptors at once (each with its own static buffer).

📦 File to Submit
Usually you’re expected to implement the following:

get_next_line.c

get_next_line_utils.c

get_next_line.h

⚙️ Main Steps
Here’s how get_next_line typically works:

Use a static buffer to store leftover data between calls.

Read from fd until you find a \n or reach EOF.

Append each read to a temporary string (a growing line).

Return the portion up to and including the first \n.

Keep the rest in the static buffer for the next call.

If no \n is found and EOF is reached, return what's left.

🔁 Typical Flow Example
Suppose you call get_next_line(fd) repeatedly on a file that contains:

kotlin
Copy
Edit
hello world\n
this is 42\n
goodbye
You should get these return values:

c
Copy
Edit
1st call → "hello world\n"
2nd call → "this is 42\n"
3rd call → "goodbye"
4th call → NULL
📌 Common Helper Functions You’ll Need
ft_strlen

ft_strchr

ft_strjoin

ft_strdup

ft_substr

You must implement these yourself (in get_next_line_utils.c).

🧪 BUFFER_SIZE
The reading chunk size is defined via the macro BUFFER_SIZE. You should:

Compile with:

bash
Copy
Edit
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
Test with different sizes: small (1), medium (10–42), large (1000+)

🧠 What You'll Learn
File I/O using read()

Handling partial reads

Memory management in dynamic strings

Persistent state using static variables

Debugging edge cases: empty files, multiple newlines, large inputs, no newline at EOF
