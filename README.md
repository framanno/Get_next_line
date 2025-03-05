# **get_next_line**

This project implements the `get_next_line` function, which reads a line of text from a file, one line at a time, until the end of the file.

---

## **Testing**

### **Mandatory Part**

1. Download the repository.
2. Open `get_next_line.c`.
3. De-comment the main function (remove the `/*` at the top and `*/` at the bottom).
4. Save the file.
5. Compile with:
   ```bash
   gcc -Wall -Werror -Wextra get_next_line.c get_next_line_utils.c -o mandatory_test
   ```
6. Execute the code:
   ```bash
   ./mandatory_test fd0.txt
   ```


### **Bonus Part**

1. Download the repository.
2. Open `get_next_line_bonus.c`.
3. De-comment the main function (remove the `/*` at the top and `*/` at the bottom).
4. Save the file.
5. Compile with:
   ```bash
   gcc -Wall -Werror -Wextra get_next_line_bonus.c get_next_line_utils_bonus.c -o bonus_test
   ```
6. Execute the code:
   ```bash
   ./bonus_test fd1.txt fd2.txt fd3.txt
   ```

---

## **Explanation with a Metaphor**

**The Librarian and the Giant Book**

Imagine you are a librarian who has to read a very large book (the file) aloud, but you can only read a limited number of characters at a time (`BUFFER_SIZE`). Additionally, you have a chalkboard on which you can write the words already read but not yet spoken aloud (`buff_data`).

Your goal is to read the book line by line and deliver each complete line to the listener. However, you might not immediately find a complete sentence that is ready to read, so you must keep track of what you’ve read so far and complete it in the next reading.

Just like a careful librarian, get_next_line ensures every line is delivered perfectly, without losing a single word.

---

**Functions:**

### 1. `get_next_line`

**Purpose**: "Reads a line from a file."

This function calls the other functions to read the file in blocks and return one line at a time. `buff_data` is a temporary memory that holds data between reads. When the file is finished, it frees everything and returns `NULL`.

---

### 2. `read_and_buffer`

**Purpose:** "Read and put in the buffer."

This function reads a chunk of data from the file and adds it to the existing buffer. It uses a temporary buffer to manage the read operation. It reads until it finds a newline (`\n`). The updated buffer is returned.

---

### 3. `read_until_eol`

**Purpose:** Reads data in blocks until it finds `\n` or the end of the file.

This function uses `read()` to get data and adds it to the main buffer. If `\n` is found, the loop ends.

---

### 4. `extract_line`

**Purpose:** Separates the first complete line from the buffer.

This function searches for the first occurrence of `\n` in the buffer. If there is any remaining data after the newline, it stores it as leftover_data. The function then returns the extracted line and keeps the remaining data intact for the next read operation.

---

### 5. `get_full_line`

**Purpose:** Completes the process by extracting a full line.

This function calls extract_line to retrieve the complete line from the buffer. It then updates the buffer by removing the extracted line. Finally, it returns the extracted line, ready for use.

---

## **Execution flow**

**Start**

1. The `get_next_line()` function is called with a file descriptor `fd`.

**get_next_line()**

2. The first thing `get_next_line()` does is check if the file descriptor `fd` is valid (i.e., between 0 and 1023) and if `BUFFER_SIZE > 0`. If it’s not valid, the function returns `NULL`.

**read_and_buffer()**

3. The `read_and_buffer()` function is called from within `get_next_line()`. This function is responsible for reading data from the file and storing it in the `buff_data` buffer.
4. A temporary buffer (`temp_buffer`) is allocated to read the data, and the `read_until_eol()` function is called to fill `buff_data` with the read data.

**read_until_eol()**

5. The `read_until_eol()` function starts reading data from the file into the temporary buffer (`temp_buffer`) until it finds a newline character (`\n`) or the end of the file (EOF).
6. It continues reading in blocks of data until one of the following conditions is met:
   - A newline character (`\n`) is found, which means a complete line has been found.
   - The end of the file (EOF) is reached.
7. The newly read data is added to `buff_data`, and the function returns.

**Return to `read_and_buffer()`**

8. After `read_until_eol()` finishes, the function returns to `read_and_buffer()` to check if the read operation was successful. If no data was read (`bytes_read == 0`) or there was an error (`bytes_read == -1`), it returns `NULL`.

**get_full_line()**

9. Once `buff_data` contains data (either a complete or partial line), the `get_full_line()` function is called from within `get_next_line()`.

**get_full_line()** then calls `extract_line()` to extract the first complete line from `buff_data`.

**extract_line()**

10. The `extract_line()` function looks for the first newline (`\n`) character in `buff_data`.
11. If a newline is found, the function allocates memory for the line and copies all the characters from `buff_data` up to and including the newline.
12. If there is remaining data in `buff_data` after the extracted line, it saves it into `leftover_data` for the next read cycle.
13. The function returns the extracted line and also sets `leftover_data` for the remaining data.

**Return to `get_full_line()`**

14. The extracted line from `buff_data` is returned to `get_next_line()`.
15. If there’s remaining data in `buff_data`, the memory is freed and the buffer is updated to point to `leftover_data`.
16. If `buff_data` is empty or `NULL`, the buffer is set to `NULL`, and the function returns `NULL`.

**Return to `get_next_line()`**

17. The `get_next_line()` function returns the extracted line to the caller.

**Repetition (if needed)**

18. If `get_next_line()` is called again, it continues from where it left off with the data in `buff_data`, trying to read and return the next line until the end of the file (EOF) is reached.

---

## **Utility Functions**

1. **`int ft_strlen`**
   - Returns the length of a string excluding the null terminator.

2. **`int *ft_strchr`**
   - Finds the first occurrence of a character in a string and returns a pointer to it, or `NULL` if not found.

3. **`char *ft_strjoin`**
   - Joins two strings with a separator.

4. **`char *ft_strdup`**
   - Duplicates a string: allocates memory and copies the source string to new memory.

5. **`char *ft_strncpy`**
   - Copies up to `n` characters from the source string to the destination string.

---

## **Meaning of `bytes_read` and `total_bytes_read` Values**

- **`== -1`:** Indicates that an error occurred during the read operation.  
- **`== 0`:** Indicates that the end of the file (EOF) has been reached.  
- **`> 0`:** Indicates that at least one byte was successfully read.  

---

## **Memory Management**

### **Static Buffer Array (`buff_data`)**

This array is defined as `static char *buff_data[1024]`, meaning it is allocated once and persists for the lifetime of the program. Each element of this array is used to store buffered data for different file descriptors.

### **Dynamic Allocation in `read_and_buffer`**

In `read_and_buffer`, the temporary buffer is dynamically allocated with:
```c
malloc((BUFFER_SIZE + 1) * sizeof(char));
```
Once the data is processed, the temporary buffer is freed with:
```c
free(temp_buffer);
```

### **Dynamic Allocation in `extract_line`**

The `extract_line` function dynamically allocates memory for the line using:
```c
malloc(sizeof(char) * (line_len + 1));
```
If there’s leftover data in the buffer after extracting a line, `leftover_data` is also dynamically allocated using `ft_strdup`.

### **Memory Deallocation**

- After extracting a line, the old buffer data is freed with `free(*buff_data)` in `get_full_line`.
- If the extracted line is `NULL` (indicating an error or end of the file), the buffer for that file descriptor is freed and set to `NULL` in `get_next_line`.

---

## **Error Handling**

### **Memory Allocation Failure**

Whenever `malloc` is called, the code checks if the allocation was successful. If not, it returns `NULL` immediately, indicating an error. For instance, if `malloc` fails in `extract_line`, the function returns `NULL`.

---

## **Credits**

A special thanks goes to the following individuals and sources that greatly contributed to this project:

- **girizzi** for his patience and support throughout the process.
- **Lo Zarlo** for his help with debugging and for providing clear, humorous explanations of stuff I struggled with.
- **Oceano** for his insightful YouTube videos that served as a fantastic learning resource.
- The creators of **42gitbook**, the ultimate guide for 42 projects.

Their support and insights were invaluable for this project—huge thanks to them all! 🙏
---

## **Bonus Files**

The **Bonus Files** reveal more about me and my background. Here’s a brief look at each:

1. **fd0.txt**  
   A beautiful and humorous song by **Quartaumentata (4a+), "Vai, vai"**—a piece written in the Calabrese dialect. It’s a catchy and lively tune that gives insight into the unique linguistic and cultural aspects of Calabria.

2. **fd1.txt**  
   The iconic soundtrack from **Monsters, Inc. (Monsters & Co.)**, a Disney-Pixar film. The best animated films ever made.

3. **fd2.txt**  
   An excerpt from **Don Quijote de la Mancha**, by **Miguel de Cervantes**. “El que no sabe gozar de la ventura cuando le viene, no debe quejarse de la adversidad cuando la siente.”

4. **fd3.txt**  
   **Déclaration des Droits de l'Homme et du Citoyen - Révolution française, 1789**. No need to add anything further

---
