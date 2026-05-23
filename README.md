
# MP3 Tag Reader and Editor in C

## Overview

This project is a command-line based MP3 Tag Reader and Editor developed using the C programming language. The application reads and modifies ID3 metadata tags present in MP3 files such as title, artist, album, year, genre, and comments.

The project demonstrates concepts of binary file handling, file parsing, command-line arguments, and metadata manipulation using C.

---

## Features

- Reads MP3 metadata tags
- Displays song title, artist, album, and genre
- Supports editing ID3 tag information
- Binary file handling using C
- Uses command-line arguments
- Supports frame-wise tag processing
- Error handling for invalid files
- Preserves MP3 audio data while editing tags

---

## Technologies Used

- C Programming
- Binary File Handling
- Structures
- Command-Line Arguments
- ID3 Tag Processing

---

## Project Structure

```text
mp3-tag-reader-c/
│
├── main.c
├── view.c
├── edit.c
├── file.h
├── sample.mp3
└── README.md
```

---

## File Description

### main.c
Controls the overall program execution and processes command-line arguments.

### view.c
Contains functions used to read and display MP3 tag information.

### edit.c
Contains functions used to modify MP3 metadata tags.

### file.h
Contains structure definitions, macros, and function declarations.

### sample.mp3
Sample MP3 file used for testing the application.

---

## Supported Tags

- Title
- Artist
- Album
- Year
- Genre
- Comment

---

## How It Works

1. The program opens the MP3 file in binary mode.
2. Reads ID3 frames from the file.
3. Extracts metadata information.
4. Displays tag details to the user.
5. Allows editing selected tag fields.
6. Writes updated data back into the MP3 file.

---

## Compilation and Execution

### Compile

```bash
gcc main.c view.c edit.c
```

### View MP3 Tags

```bash
./a.out -v sample.mp3
```

### Edit MP3 Tags

```bash
./a.out -e -t "New Title" sample.mp3
```

---
## Usage

```text
usage: mp3tag -[tTaAycg] "value" file.mp3
       mp3tag -v file.mp3
```

---

## OPTIONS

```text
-t    Modifies a Title tag
-a    Modifies an Artist tag
-A    Modifies an Album tag
-y    Modifies a Year tag
-c    Modifies a Comment tag
-g    Modifies a Genre tag
-h    Displays this help information
-v    Prints version information
```

## Sample Output

```text
----------------------------------------
MP3 TAG READER AND EDITOR
----------------------------------------

Title   : Sunny Sunny
Artist  : Yo Yo Honey Singh
Album   : Yaariyan
Year    : 2014
Genre   : Pop
Comment : Nice Song
```

---

## Concepts Covered

- Binary File Handling
- ID3 Tag Processing
- Metadata Extraction
- File Parsing
- Structures in C
- Command-Line Argument Handling

---

## Applications

- Music Metadata Management
- MP3 Information Systems
- File Processing Projects
- Embedded File Utilities
- Multimedia Software Development

---

## Future Enhancements

- Add support for ID3v2 advanced frames
- Add album art extraction
- Develop graphical user interface
- Support batch editing of MP3 files
- Add playlist management features

---

## Conclusion

This project demonstrates the implementation of an MP3 Tag Reader and Editor using the C programming language. It provides practical exposure to binary file handling and metadata processing concepts while preserving original MP3 audio content.

---

## Author

Gagan Bhairamatti
