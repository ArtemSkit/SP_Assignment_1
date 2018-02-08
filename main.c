/** @file main.cpp
*
* This file contains the kernel's
* main() function.
*
* This c program prompts user for the weight of
* the article, the zone to which it is going and whether it should go by air or it is local,
* and then print out the correct stamp.
*
* @author Artem Skitenko
*/
#include <stdio.h>
#include <math.h>

void getWeightAndTransport(float* data) {
	do {
		printf("Enter weight of the package in ounces = ");
		scanf("%f",data);
		if (data[0] <= 0) printf("The weight is too small. Try again.\n");;
	} while (data[0] <= 0);
	do {
		printf("Land: 1 Air: 2 = ");
		scanf("%f",&data[1]);
		if (data[1] != 1 && data[1] != 2)
			printf("The value mast be 1 or 2. Try again.\n");
	} while (data[1] != 1 && data[1] != 2);
	// Since we increase the price every 1/2 ounce we need to multiply weight by 2
	data[0] *= 2;
	// Roundup the weight value
	data[0] = ceil(data[0]);
}

double countPrice(float weight, float landAir) {
	float price = 0;
	short zone;
	if (weight > 1) {
		do {
			printf("Select zone: 1, 2 or 3 = ");
			scanf("%d",&zone);
			if (zone < 1 || zone > 3)
				printf("The value mast be 1, 2 or 3. Try again.\n");
		} while (zone < 1 || zone > 3);
		--weight;
		switch (zone)
		{
		case 1: price += landAir == 1 ? 0.5 * weight * 0.49 : 0.4 * weight * 0.9;
			break;
		case 2: price += landAir == 1 ? 0.65 * weight * 0.49 : 0.6 * weight * 0.9;
			break;
		case 3: price += landAir == 1 ? 0.8 * weight * 0.49 : 0.85 * weight * 0.9;
		}
	}
	// If weight is less than 1/2 ounce we don't need to ask the zone since it won't change the price
	if (landAir == 1) price += 0.49;
	else price += 0.9;
	return round(price * 100) / 100;
}

void printStamp(float price, float landAir) {
	printf(" _________\n");
	printf("|   USA   |\n");
	printf("|  " "$%.2f%s|\n", price, price>=10? " ":"  ");
	printf("|  %s |\n",landAir == 1 ? "Local " : "By Air");
	printf("|_________|\n");
}

int main() {
	float data[2] = { 0,0 };
	float price = 0;
	do {
		getWeightAndTransport(data);
		price = countPrice(data[0], data[1]);
		if (price > 20.0) {
			printf("The price is greater than $20. Start over.\n");
		}
	} while (price > 20.0);
	printStamp(price, data[1]);
	getchar();
	getchar();
	return 0;
}
