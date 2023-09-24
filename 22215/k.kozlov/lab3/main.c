#include "unistd.h"
#include "stdio.h"
#include "errno.h"

// ��� ���������� ��������������� ��������� /home/students/22200/k.kozlov/NSU-OS-2023/22215/k.kozlov/lab3/script_for_groupmates

/**
 * ���� - ������, ������� ����� ������ � ������
 * ����
 * ���� - ������������������ ���� � ���������� � ��������� �� �����
 * 
 * fopen(3)(char* path, char* mode) - ��������� ���� �� ��������� ���� � �������� ������ � ���������� ��������� ���� FILE*
 *   � ������ ������ ���������� NULL � ���������� ��� ������ � errno
 *   �������� �£����� ��� open(2):
 *     - ��������� ���������� ����� �� ���������� ����. 
 *       ���������� - ��������� ���� �����, ����������� � ���������� �������� ����� file_t.
 *         � �������� ������ ����� vnode, ����� (offset) � �����, ���������� �� ����� ������� � ����� � ������ �����
 *     - ����� ������� ����� ���������
 * 
 * 
 * fclose(3)(FILE* stream) - ��������� ���� �� ��������� FILE*. ���������� 0 � ������ ������
 *   ������ �£����� ��� close(2):
 *     - ��������� ����������, ����������� �� ���������� � ����� file_t
 *       ���� ��� ��������� ���������� �� file_t, �� ��� ��������� ����� ���������.
 *       ���� ������� ��������� ��������� file_t, �� ����� ������� ��������� vnode
 * 
*/
void tryOpen(char* fileName) {
  uid_t uid = getuid(), euid = geteuid();
  printf("Reading file \"%s\"...\n", fileName);
  printf("UID: %d / EUID: %d\n", uid, euid);
  FILE* fStream = fopen(fileName, "r");
  if (fStream) {
    printf("File was read successfully\n");
    if (fclose(fStream) != 0)
      perror("Failed to close file");
    else
      printf("File was closed\n");
  }
  else
    perror("Failed to read file");
}

/*
�������� ID - �����, ������� � �������� ������������ � Unix
����������� ID - �����, ������� ���������� ����� �������. 
�� ��������� ��������� ���������.

setuid ��� � ������ ������� ����� ��������� ��������� ��� � ����������� ID ��������� �����.
setuid(2) - ��������� �� root-������������ ���� ���������� ���� �������� ID ����, � ��������� ��������, �������� ���� ����������.
  root ������������ ����� ���������� ���� ����� ����������� euid
*/

void setuidWrapper(uid_t newEUID) {
  printf("Setting EUID to %d...\n", newEUID);
  if (setuid(newEUID) == 0)
    printf("Success!\n");
  else 
    perror("Failed to set EUID");
}

int main(int argc, char** argv) {
  char fileName[5] = "file";
  tryOpen(fileName);
  printf("\n");
  setuidWrapper(getuid());
  printf("\n");
  tryOpen(fileName);
}