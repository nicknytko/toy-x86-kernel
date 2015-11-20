	;; filesystem node
	;; 260 bytes null terminated name
	;; dword permissions mask
	;; word  user uid
	;; word  group gid
	;; word  flags
	;; dword length
	;; dword inode
	;; dword pointer to read file
	;; dword pointer to write file
	;; dword pointer to open file
	;; dword pointer to close file
	;; (286 bytes)
	
	;; read function:
	;; dword pointer to file node
	;; dword pointer to buffer to read to
	;; dword number of bytes to read
	;; byte offset
	;; returns: dword number of bytes read

	;; write function:
	;; dword pointer to file node
	;; dword pointer to buffer to write
	;; dword number of bytes
	;; byte offset
	;; returns: dword number of bytes written

	;; open function:
	;; dword pointer to file descriptor

	;; close function:
	;; dword pointer to file descriptor
