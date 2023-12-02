#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


struct Student {
	int num;
	int gradebook;
	int marks[5];
	char surname[15] = { NULL }, name[15] = { NULL }, patronymic[15] = { NULL };
};

Student* ReadTxt(int& cnt)
{
	FILE* f = fopen("List.txt", "r");
	if (f == 0)
		exit(-1);
	fscanf_s(f, "%i\n", &cnt);
	Student* mas = (Student*)malloc(sizeof(Student) * cnt);
	for (int i = 0; i < cnt; i++)
		fscanf_s(f, "%i %s %s %s %i %i %i %i %i %i\n", &mas[i].num, mas[i].surname, 15, mas[i].name, 15, mas[i].patronymic, 15, &mas[i].gradebook,
			&mas[i].marks[0], &mas[i].marks[1], &mas[i].marks[2], &mas[i].marks[3], &mas[i].marks[4]);
	fclose(f);
	return mas;
}

void PrintTable(Student* mas, int cnt)
{
	printf("_____________________________________________________________________________________________________________\n");
	printf("| №|   Фамилия|       Имя|       Отчество|  № билета| Физкультура|Математика|Программирование|Физика|История|\n");

	for (int i = 0; i < cnt; i++)
		printf_s("|%2i|%10s|%10s|%15s|%10i|%12i|%10i|%16i|%6i|%7i|\n", mas[i].num, mas[i].surname, mas[i].name, mas[i].patronymic, mas[i].gradebook,
			mas[i].marks[0], mas[i].marks[1], mas[i].marks[2], mas[i].marks[3], mas[i].marks[4]);
	printf("-------------------------------------------------------------------------------------------------------------\n");
}

void SurnameSort(Student* mas, int cnt)
{
	bool flag = true;
	Student temp;
	while (flag)
	{
		flag = false;
		for (int i = 0; i < cnt - 1; i++)
			if (strcmp(mas[i].surname, mas[i + 1].surname) > 0)
			{
				temp = mas[i];
				mas[i] = mas[i + 1];
				mas[i + 1] = temp;
				flag = true;
			}
	}
}

void SubjectSort(Student* mas, int cnt, int subject)
{
	bool flag = true;
	Student temp;
	while (flag)
	{
		flag = false;
		for (int i = 0; i < cnt - 1; i++)
			if (mas[i].marks[subject] < mas[i + 1].marks[subject])
			{
				temp = mas[i];
				mas[i] = mas[i + 1];
				mas[i + 1] = temp;
				flag = true;
			}
	}
}

void FindSurname(Student* mas, int& cnt)
{
	char surname[15] = { NULL };
	printf("Введите фамилию: ");
	int surn;
	while ((surn = getchar()) != '\n' && surn != EOF) {}
	gets_s(surname, 10);
	int counter = 0;
	Student temp;
	for (int i = 0; i < cnt; i++)
		if (strcmp(mas[i].surname, surname) == 0)
		{
			temp = mas[counter];
			mas[counter] = mas[i];
			mas[i] = temp;
			counter++;
		}
	cnt = counter;
}

void Sred(Student* mas, int& cnt)
{
	double stud[10] = {0};
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			stud[i] += mas[i].marks[j];
		}
	}
	int counter = 0;
	Student temp;
	for (int i = 0; i < cnt; i++)
		if (stud[i]/5>=3)
		{
			temp = mas[counter];
			mas[counter] = mas[i];
			mas[i] = temp;
			counter++;
		}
	cnt = counter;
}

int main()
{
	system("chcp 1251");

	int cnt, choice, key;
	Student* mas = ReadTxt(cnt);
	PrintTable(mas, cnt);
	bool flag = true;

	while (flag)
	{
		do
		{
			printf("1 - Отсортировать таблицу по алфавиту. 2 - Отсортировать таблицу по предмету. 3 - Найти студента по фамилии. 4 - Средний балл. 0 - Закончить работу.\n");
			scanf_s("%i", &choice);
		} while (choice > 4 or choice < 0);
		switch (choice)
		{
		case 1:
			SurnameSort(mas, cnt);
			PrintTable(mas, cnt);
			break;
		case 2:
			do
			{
				printf("Отсортировать по: 1 -  Физкультура. 2 - Математика. 3 - Программирование. 4 - Физика. 5 - История\n");
				scanf_s("%i", &key);
			} while (key > 5 or key < 1);
			SurnameSort(mas, cnt);
			SubjectSort(mas, cnt, key - 1);
			PrintTable(mas, cnt);
			mas = ReadTxt(cnt);
			break;
		case 3:
			FindSurname(mas, cnt);
			if (cnt == 0)
				printf("Студент с такой фамилией не найден.\n");
			else
				PrintTable(mas, cnt);
			mas = ReadTxt(cnt);
			break;
		case 4:
			Sred(mas, cnt);
			PrintTable(mas, cnt);
			break;
		case 0:
			flag = false;
			break;
		}
	}
	return 0;
}
// сред балл для кажд студента и вывести студента у которых средний балл от 3 до 5