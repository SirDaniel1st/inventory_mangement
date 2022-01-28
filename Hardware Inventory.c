#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Stock{     // 5 ARRAYS
	int itemId[1000];
	double costPrice[1000];
	int amt[1000];
	char name[1000][1000];
	char supplier[1000][1000];
	int totalStocks;
};
struct Bill{
	int itemid[1000];
	int amt[1000];
	double sellingP[1000];
	double totalP;
};

struct Bill bill;

struct Stock Stocks;

void readData(){   // READS DATA FROM TEXT FILE
 	FILE *fp;
	int id=0 , amt=0 , i=0;
	double cPrice=0.00;
	char name[1000];
	char supplier[1000];
	fp= fopen("StockList.txt", "r");
	while(!feof(fp)){
		//printf("test");
		fscanf(fp,"%d %lf %d",&id,&cPrice,&amt);
		fscanf(fp, "%s",name);
		fscanf(fp,"%s",supplier);
		Stocks.itemId[i]=id;
		Stocks.costPrice[i]=cPrice;
		Stocks.amt[i]=amt;
		strcpy(Stocks.name[i],name);
		strcpy(Stocks.supplier[i],supplier);
		i++;
	}
	Stocks.totalStocks=i;
	fclose(fp);
}


void checkOut(){ // FUNCTION TO GENERATE A CUSTOMER'S BILL
	int id,amount, i=0, j=0;
	struct Bill bill;
	printf("Enter the Item ID :");
	scanf("%d", &id);
	printf("Enter the Item Amount :");
	scanf("%d", &amount);
	while (id!=-1){
		for(j=0;j<1000;j++){
			if(id==Stocks.itemId[j]){
				bill.itemid[i]=id;
				bill.amt[i]=amount;
				bill.sellingP[i]=((Stocks.costPrice[j]*1.8)+Stocks.costPrice[j]*0.125);
				bill.totalP=bill.totalP + amount*bill.sellingP[i];
				break;
			}
		}
		printf("Enter the Item ID :");
		scanf("%d", &id);
		printf("Enter the Item Amount :");
		scanf("%d", &amount);
	}
	printf("\n******TOTAL BILL******\n");
	int p=0;
	for(p=0; p<i; p++){
		printf("Item Id : %d",bill.itemid[p]);
		printf("Item Amount : %d",bill.amt[p]);
		printf("Item Price : $ %lf",bill.sellingP[p]);
		printf("\n-----------------------------------\n");		
	}
	printf("\n*****TOTAL PRICE : $ %lf \n\n",bill.totalP);
}

void addItem(){ // FUNCTION TO ADD AN ITEM TO THE STOCK
	int i=Stocks.totalStocks+1;
	//printf("%d",i);
	printf("Enter new Item ID :");
	scanf("%d",&Stocks.itemId[i]);
	printf("Enter Item's name : ");
	scanf("%s",Stocks.name[i]);
	printf("Enter Item's Supplier : ");
	scanf("%s",Stocks.supplier[i]);
	printf("Enter Price : $");
	scanf("%lf",&Stocks.costPrice[i]);
	printf("Enter the amount for the item : ");
	scanf("%d", &Stocks.amt[i]);
	printf("ITEM ADDED!\n\n");
	printf("%d %d %lf \n%s %s",Stocks.itemId[i],Stocks.amt[i],Stocks.itemId[i],Stocks.name[i],Stocks.supplier[i]);
	Stocks.totalStocks++;
}

void deleteItem(){ //FUNCTION TO DELETE AN ITEM FROM THE STOCK
	int id;
	printf("Enter the Item ID to be deleted :");
	scanf("%d",&id);
	int i=0;
	while(i!=Stocks.totalStocks){
		if(Stocks.itemId[i] == id){
			Stocks.itemId[i]=-9999;
			printf("Item Deleted \n\n");
			return;
		}
		i++;
	}
	printf("Item not found in database!\n\n");
}

void fileUpdate(){ // FUNCTION TO UPDATE THE FILE
	FILE *fp;
	fp= fopen("StockList.txt", "w");
	int i=0;
	while(i!=Stocks.totalStocks){
		if(Stocks.itemId[i]!=-9999){
			fprintf(fp,"%d %lf %d\n%s\n%s\n",Stocks.itemId[i],Stocks.costPrice[i],Stocks.amt[i],Stocks.name[i],Stocks.supplier[i]);
		}
		i++;
	}
	printf("File Updated!\n\n");
	fclose(fp);
}

void changeSupplier(){ // FUNCTION TO CHANGE THE SUPPLIER OF AN ITEM
	int id, i;
	bool found=false;
	printf("Enter the Item Id of the Item you would like to change supplier to : ");
	scanf("%d",&id);
	for (i=0;i<Stocks.totalStocks;i++){
		if(Stocks.itemId[i]==id){
			printf(" Current Supplier : %s \n",Stocks.supplier[i]);
			printf(" Enter the new Supplier :");
			scanf("%s",Stocks.supplier[i]);
			found=true;
		}
	}	
	if(found==false){
		printf("Item not found\n\n");
	}
	else{
		printf("Item Supplier Updated\n\n");
	}
}

void generateReport(){ // FUNCTION TO GENERATE A REPORT OF STOCK ITEMS THAT ARE LESS THAN 20
	FILE *fp;
	fp= fopen("Report.txt", "w");
	int i=0;
	fprintf(fp,"-----GENERATED REPORT-----\n");
	fprintf(fp,"---STOCKS LESS THAN 20---\n");
	while(i!=Stocks.totalStocks){
		if(Stocks.amt[i]<20){
			fprintf(fp," ITEM ID : %d ,\n ITEM AMOUNT : %d ,\n ITEM COST PRICE : $ %lf \n ITEM NAME : %s , ITEM SUPPLIER : %s \n\n",Stocks.itemId[i],Stocks.amt[i],Stocks.costPrice[i],Stocks.name[i],Stocks.supplier[i]);
		}
		i++;
	}
	printf("REPORT GENERATED TO REPORT.TXT!\n\n");
	fclose(fp);
}

int main(){     // GENERATES THE MENU
	readData();
	int response=0;
	while (response!=6){
		printf("---------------------MENU----------------------- \n");
		printf("1. Check Out Items \n");
		printf("2. Add Item to Database \n");
		printf("3. Delete Item from Database \n");
		printf("4. Change Supplier of Item \n");
		printf("5. Generate Report for Restock \n");
		printf("6. Quit\n");
		printf("------------------------------------------------\n");
		printf("\n Choose an option : ");
		scanf("%d",&response);
		if(response==1){
			checkOut();
		}
		if(response==2){
			addItem();
		}
		if(response==3){
			deleteItem();
		}
		if(response==4){
			changeSupplier();
		}
		if(response==5){
			generateReport();
		}
		
	}
	fileUpdate(Stocks);
	printf("Quttting.....");
	return 1;
}
