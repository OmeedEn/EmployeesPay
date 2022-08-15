#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

typedef struct employee
{
	char name[20];
	float hours;
	float rate;
	float gross;
	float tax;
	float overtimehours;
	float base;
	float overtimepay;
	float total;
}EMP;

int menu(EMP* q, int count)
{
	int choice;
	puts("\nMain Menu:");
	puts("\n1. Add Employee");
	puts("\n2. Edit Employee");
	puts("\n3. Print a single employee");
	puts("\n4. Print ALL employees");
	puts("\n5. Quit\n");

	scanf("%d", &choice);

	switch (choice)
	{
	case 1:
	{
		load(q);
		gp(q);
		taxowed(q);
		menu(q, count);
	}
	case 2:
	{
		edit(count, q);
		menu(q, count);
	}
	case 3:
	{
		gp(q);
		printone(q, count);
		menu(q, count);
	}
	case 4:
	{
		gp(q);
		printall(q, count);
		menu(q, count);
	}
	case 5:
	{
		gp(q);
		printtofile(q, count);
		exit(0);
	}
	}
	return choice;
}

int load(EMP* e)
{
	int num = 0;
	printf("\nHow many employees would you want to add? ");
	scanf("%d", &num);

	for (int i = 0; i < num; i++)
	{
		printf("\nEnter name: ");
		scanf_s("%s", &e[i].name, 20);
		if (e[i].name == '-' && e[i].name == '1')
			break;

		printf("\nEnter hourly rate: ");
		scanf("%f", &e[i].rate);
		if (e[i].rate == -1)
			break;

		printf("Enter hours worked: ");
		scanf("%f", &e[i].hours);
		if (e[i].hours == -1)
			break;

	}
	return num;
}

int loadfromfile(EMP y[])
{
	FILE* data;
	char* fname;
	int c = 0;

	printf("Whats the name of the file: ");
	scanf(" s", &fname);

	data = fopen(fname, "r");

	if (data == 0)
	{
		printf("error");
		return -1;
	}

	for (int i = 0; i < 10; i++)
	{
		fscanf(data, "f", &y[i].name);
		if (y[i].name == '-' && y[i].name == '1')
			break;

		fscanf(data, "f", &y[i].hours);
		if (y[i].rate == -1)
			break;

		fscanf(data, "f", &y[i].rate);
		if (y[i].hours == -1)
			break;

		c++;
	}

	fclose(data);
	return c;

}

int edit(int count, EMP func[])
{
	int choice;

	printf("\nWhich employee would you like to edit?\n");

	for (int i = 0; i < count; i++)
	{
		printf("Employee %d: %s\n", i, func[i].name);
	}

	scanf("%d", &choice);

	while (choice < 0 || choice >= count)
	{
		printf("\nEnter a valid option: \n");
		scanf("%d", &choice);
	}

	if (choice == 0)
	{
		choice++;
	}

	for (int i = 0; i < choice; i++)
	{
		printf("\nEnter a new name: ");
		scanf("%s", &func[choice].name);

		printf("\nEnter hours worked: ");
		scanf("%f", &func[choice].hours);

		printf("\nEnter rate: ");
		scanf("%f", &func[choice].rate);
	}


}

int printone(EMP* c, int cho)
{
	int choose;
	printf("Choose an employee: \n");

	for (int i = 0; i < cho; i++)
	{
		printf("Employees %d: %s\n", i, c[i].name);
	}
	scanf("%d", &choose);

	taxowed(c, choose);

	printf("\nPay to: %s", c[choose].name);
	printf("\nHourly rate: $%f", c[choose].rate);
	printf("\nHours worked: %f", c[choose].hours);
	printf("\nGross pay: %f", c[choose].gross);
	printf("\nBase pay: %f", c[choose].base);
	printf("\nOvertime pay: %f", c[choose].overtimepay);
	printf("\nTaxes paid: %f", c[choose].tax);
}

int printall(EMP b[], int count)
{
	taxowed(b, count);
	for (int i = 0; i < count; i++)
	{
		printf("\nPay to: %s", b[i].name);
		printf("\nHourly rate: $%.2f", b[i].rate);
		printf("\nHours worked: %.2f", b[i].hours);
		printf("\nGross pay: %f", b[i].gross);
		printf("\nBase pay: %f", b[i].base);
		printf("\nOvertime pay: %f", b[i].overtimepay);
		printf("\nTaxes paid: %f", b[i].tax);
	}
	return 0;
}

void printallnames(EMP j[], int count)
{
	for (int i = 0; i < count; i++)
	{
		printf("\n %d %s", i, &j[i].name, 20);
	}
}

int printtofile(EMP h[], int count)
{
	FILE* employeedata;

	char newfilename[30];
	printf("Save file as?: ");
	scanf("%s", &newfilename);

	employeedata = fopen(newfilename, "w");
	taxowed(h, count);


	for (int i = 0; i < count; i++)
	{
		fprintf(employeedata, "\nPay to: %s", h[i].name);
		fprintf(employeedata, "\nHourly rate: $%0.2f", h[i].rate);
		fprintf(employeedata, "\nHours worked: %0.2f", h[i].hours);
		fprintf(employeedata, "\nGross pay: %f", h[i].gross);
		fprintf(employeedata, "\nBase pay: %f", h[i].base);
		fprintf(employeedata, "\nOvertime pay: %f", h[i].overtimepay);
		fprintf(employeedata, "\nTaxes paid: %f", h[i].tax);
	}

	fclose(employeedata);
	return 0;
}

int keyboardfile()
{
	char input;

	printf("Do you want to load data from a file or from the keyboard?\n type F for file OR K for keyboard: \n");
	scanf("%c", &input);

	if (input == 'F')
		return 0;
	if (input == 'K')
		return 1;
}

int gp(EMP d[])
{
	double totalpay;
	float overtimehours;

	for (int i = 0; i < 5; i++)
	{
		d[i].base = d[i].hours * d[i].rate;

		if (d[i].hours > 40)
		{
			d[i].overtimepay = 1.5 * d[i].rate * (d[i].hours - 40);
			d[i].gross = 40 * d[i].rate + d[i].overtimepay;
			totalpay += d[i].gross;
		}
		else
		{
			d[i].overtimepay = 0;
			d[i].gross = d[i].hours* d[i].rate;
			totalpay += d[i].gross;
		}
	}
	return totalpay;
}

int taxowed(EMP v[], int b)
{
	for (int i = 0; i < b; i++)
	{
		v[i].tax = v[i].gross * 0.2;
		v[i].total = v[i].gross - v[i].tax;
		return v[i].tax;
	}
}

int main()
{
	int count = 0;
	struct employee r[10];
	int counts = keyboardfile();

	if (counts == 1)
		count = load(&r);
	if (counts == 0)
		count = loadfromfile(r);

	menu(r, count);

	return 0;
}