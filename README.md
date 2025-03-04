# Get_next_line
This code implements the get_next_line function, which reads a line of text from a file, one line at a time, until the end of the file.

TO TEST MANDATORY PART


1. Download the repository
2. Open get_next_line.c
3. De-comment the main function (cancel these symbols: " /* " at the top and " */"  at the bottom of the function)
4. Save file
5. Compile with "gcc -Wall -Werror -Wextra get_next_line.c get_next_line_utils.c"
6. Execute code "./a.out fd0.txt"

TO TEST BONUS PART


1. Download the repository
2. Open get_next_line_bonus.c
3. De-comment the main function (cancel these symbols: " /* " at the top and " */"  at the bottom of the function)
4. Save file
5. Compile with "gcc -Wall -Werror -Wextra get_next_line_bonus.c get_next_line_utils_bonus.c"
6. Execute code "./a.out fd1.txt fd2.txt fd3.txt"

----------------------------------------------------------------------------------------------------------------
EXPLANATION WITH A METAPHORE


Metaphor: The Librarian and the Giant Book

Imagine you are a librarian who has to read a very large book (the file) aloud, but you can only read a limited number of characters at a time (BUFFER_SIZE). Additionally, you have a chalkboard on which you can write the words already read but not yet spoken aloud (buff_data).

Your goal is to read the book line by line and deliver each complete line to the listener. However, you might not immediately find a complete sentence that is ready to read, so you must keep track of what you’ve read so far and complete it in the next reading.

get_next_line: You, the librarian, call upon your assistants to read and manage the data.

read_and_buffer: This is your assistant who takes the book and reads it piece by piece, adding it to the chalkboard if necessary.

read_until_eol: This helper reads the book and waits to find a point (the \n character) because that means the sentence is complete.

extract_line: This assistant extracts the complete sentence from the chalkboard and writes it on a note to be delivered.

get_full_line: This is the final step: clearing the chalkboard and ensuring there’s space for the next reading.

---------------------------------------------------------------------------------------------------------------

PROJECT OVERVIEW


5 functions:
1. GET_NEXT_LINE
Calls the other functions to read the file in blocks and return one line at a time.
 buff_data is a temporary memory that holds data between reads.
 If the file is finished, it frees everything and returns NULL.

Procedure:

Initial call.

a. The file is open and the buffer is empty.
read_and_buffer fills buff_data with the first chunk of data.
Next call.

b. get_full_line extracts the first complete line.
The buffer keeps the remaining data for the next read.
When the file is finished

c. read_and_buffer no longer reads data.
buff_data is freed, and get_next_line returns NULL.

2. READ_AND_BUFFER
"Read and put in the buffer."
Reads a chunk of data from the file and adds it to the existing buffer.
It uses a temporary buffer to manage the read operation.
It reads until it finds a newline (\n). Returns the updated buffer.

Procedure:

a. The buffer is empty or contains partial data.
b. The function allocates a temporary buffer and reads a block of data.
c. The data is merged with what’s already in buff_data.
d. The temporary buffer is freed.
e. The updated buffer is returned.
3. READ_UNTIL_EOL
Reads data in blocks until it finds \n or the end of the file.
It uses read() to get data and adds it to the main buffer.
If \n is found, the loop ends.

Procedure:

a. First cycle:
buff_data is empty.
A chunk of the file is read and stored.
b. Second cycle:
Check if \n is found.
If not, read another chunk and add it.
c. When \n is found:
The cycle ends, and the buffer with the complete or partial line is returned.

4. EXTRACT_LINE
a. Separates the first complete line from the buffer.
b. Finds the first \n.
c. If there’s data after the first line, it saves it as leftover_data.
d. Returns the line and keeps the remaining data intact.

5. GET_FULL_LINE
a. Calls extract_line to get the complete line.
b. Updates the buffer by removing the extracted line.
c. If there’s no more data, sets the buffer to NULL.
d. Returns the line ready for use.

5 utils functions:
1. int	ft_strlen;

	Function that returns the length of a string excluding the null terminator.

2. int	*ft_strchr;

	Function that finds the first occurrance of a character in a string and returns a pointer to 		it, or NULL if not find.

3. char	*ft_strjoin;

	Function that joins strings with separator.

4. char	*ft_strdup;

	Function that "duplicates" a string:  allocates memory and copies the source string to new 		memory.

5. char	*ft_strncpy;

	Function that copies up to n characters from source string to destination string.

MEMORY ALLOCATION


Static buffer array (buff_data):

This array is defined as static char *buff_data[1024];, which means it is allocated once and persists for the lifetime of the program. 

Each element of this array is used to store buffered data for different file descriptors.

Dynamic allocation in read_and_buffer:

In read_and_buffer, the buffer temp_buffer is dynamically allocated with malloc((BUFFER_SIZE + 1) * sizeof(char));. This buffer temporarily holds data read from the file.

After the data is processed, temp_buffer is freed using free(temp_buffer);, ensuring we don't leak memory.

Dynamic allocation in extract_line:

The extract_line function dynamically allocates memory for the line using malloc(sizeof(char) * (line_len + 1));.

If there’s leftover data in the buffer after extracting a line, the leftover_data is also dynamically allocated using ft_strdup.

Memory Deallocation
Freeing allocated buffers:

After extracting a line, the old buffer data is freed with free(*buff_data); in get_full_line.

If the extracted line is NULL, indicating an error or end of the file, the buffer for that file descriptor is freed and set to NULL in get_next_line.

Error Handling
Memory allocation failure:

Whenever malloc is called, the code checks if the allocation was successful. If not, it returns NULL immediately, indicating an error.

For instance, if malloc fails in extract_line, the function returns NULL.
