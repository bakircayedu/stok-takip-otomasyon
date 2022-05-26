#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char ad[20];
    int id;
} kategori;

typedef struct
{
    int kodu;
    kategori ktg;
    char adi[20];
    float satis_fiyati;
    int stok_miktari;
} urun;
typedef struct
{
    int plaka;
    char ad[20];
} sehir;
typedef struct
{
    int no;
    char ad[20];
    char adres[100];
    sehir shr;
} tedarikci;
typedef struct
{
    int gun,ay,yil;
} tarih;
typedef struct
{
    int stok_id;
    int tdrNo;
    int urun_kod;
    int alis_miktar;
    float alis_fiyat;
    tarih trh;
} stok;


//URUN FONKSIYONLARI
void urun_ekle(urun urunler[],urun yedekUrun[ ],urun *ptrUrun[],int *i)
{
    int k=*i;
    int x=0;
    FILE *fp=fopen("Urun.txt","r");
    while(!feof(fp))
    {
        //AYNI NUMARADA URUN VARMI KONTOL YAPILIYOR
        fscanf(fp,"%d %s %s %f %d",&yedekUrun[x].kodu,&yedekUrun[x].adi,&yedekUrun[x].ktg.ad,&yedekUrun[x].satis_fiyati,&yedekUrun[x].stok_miktari);

        if(yedekUrun[x].kodu==ptrUrun[k]->kodu)
        {
            printf("\n\nAyni Urun Koduna Sahip Bir Urun Var!!\n");
            printf("!!Lutfen urun kodunuzu kontrol edin.\n");
            printf("!!Yeni bir urun kodu deneyin yada bu urun koduyla islem icin ANAMENU den stok kismina gidiniz\n\n");
            return ;
        }
        x++;
    }
    fclose(fp);
    fp=fopen("Urun.txt","a");
    if(fp==NULL)
    {
        printf("!Urun Dosyasi Acilmadi!");

    }
    fprintf(fp,"\n%d %s %s %2.f %d",ptrUrun[k]->kodu,ptrUrun[k]->adi,ptrUrun[k]->ktg.ad,ptrUrun[k]->satis_fiyati,ptrUrun[k]->stok_miktari,ptrUrun[k]->stok_miktari);
    fclose(fp);

}
void urun_guncelle(urun yedekurun[],int urunkodu)
{
    FILE *fp=fopen("Urun.txt","r");
    int i=0;
    char satir;

    while(!feof(fp))
    {
        fscanf(fp,"%d %s %s %f %d",&yedekurun[i].kodu,&yedekurun[i].adi,&yedekurun->ktg.ad,&yedekurun[i].satis_fiyati,&yedekurun[i].stok_miktari);
        if(yedekurun[i].kodu==urunkodu)
        {

            printf("Urun Kodu:\n");
            scanf("%d",&yedekurun[i].kodu);
            printf("Urun Adi:\n");
            scanf("%s",&yedekurun[i].adi);
            printf("Urun Kategori Adi:\n");
            scanf("%s",&yedekurun[i].ktg.ad);
            printf("Urun Fiyati:\n");
            scanf("%f",&yedekurun[i].satis_fiyati);
            printf("Urun Stok Miktari:\n");
            scanf("%d",&yedekurun[i].stok_miktari);
        }
        i++;
    }
    fclose(fp);
    fopen("Urun.txt","w");
    for(int a=0; a<(i-1); a++)
    {
        fprintf(fp,"%d %s %s %3f %d\n",yedekurun[a].kodu,yedekurun[a].adi,yedekurun[a].ktg.ad,yedekurun[a].satis_fiyati,yedekurun[a].stok_miktari);
    }
    fclose(fp);
}
void urun_sil(urun yedekUrun[])
{
    FILE *fp=fopen("Urun.txt","r");
    int i=0,a=0,k=0,l=0;
    int urunNo;
    if(fp==NULL)
    {
        printf("Dosya Acilmadi");
    }
    printf("Silinecek Urun No: ");
    scanf("%d",&urunNo);

    while(!feof(fp))
    {
        fscanf(fp,"%d %s %s %f %d",&yedekUrun[i].kodu,&yedekUrun[i].adi,&yedekUrun[i].ktg.ad,&yedekUrun[i].satis_fiyati,&yedekUrun[i].stok_miktari);
        if(yedekUrun[i].kodu==urunNo)
        {
            l=i;
            k++;
        }
        i++;
    }

    fclose(fp);
    fp = fopen("Urun.txt","w");
    for(a=0; a<(i-1); a++)
    {
        if(yedekUrun[a].kodu==yedekUrun[l].kodu)
        {
            strcpy(yedekUrun[a].adi,yedekUrun[a+1].adi);
            strcpy(yedekUrun[a].ktg.ad,yedekUrun[a+1].ktg.ad);
            yedekUrun[a].kodu = yedekUrun[a+1].kodu;
            yedekUrun[a].satis_fiyati=yedekUrun[a+1].satis_fiyati;
            yedekUrun[a].stok_miktari=yedekUrun[a].stok_miktari;
        }
    }
    if(k==0)
    {
        printf("Urun Bulunamadi!\n");
        return;
    }
    for(a=0; a<(i-2); a++)
    {
        fprintf(fp,"%d %s %s %f %d\n\n",yedekUrun[a].kodu,yedekUrun[a].adi,yedekUrun[a].ktg.ad,yedekUrun[a].satis_fiyati,yedekUrun[a].stok_miktari);
    }
    fclose(fp);
}
void urun_listele()
{
    FILE *fp;
    fp=fopen("Urun.txt","r");
    printf("--------------------------------------------\n");
    while(!feof(fp))
    {
        fputchar(fgetc(fp));
    }
    printf("--------------------------------------------\n");
    fclose(fp);
}

//TEDARIKCI FONKSIYONLARI
void tedarikci_ekle(tedarikci tdr[],tedarikci *pTdr[],int *t,tedarikci yedekTdr[])
{
    int y=*t;
    int z=0;
    FILE *fp;
    fp=fopen("Tedarikci.txt","r");
    while(!feof(fp))
    {
        fscanf(fp,"%d %s %s %s",&yedekTdr[z].no,&yedekTdr[z].ad,&yedekTdr[z].adres,&yedekTdr[z].shr.ad);
        if(yedekTdr[z].no==pTdr[y]->no)
        {
            printf("Bu no da tedarikci bulunuyor!! Lutfen baska no girerek tekrar deneyin menuden.");
            return ;
        }
        z++;
    }
    fclose(fp);
    fp=fopen("Tedarikci.txt","a");
    if(fp==NULL)
    {
        printf("!Urun Dosyasi Acilmadi!");

    }
    fprintf(fp,"\n%d %s %s %s",pTdr[y]->no,pTdr[y]->ad,pTdr[y]->adres,pTdr[y]->shr.ad);

    fclose(fp);
}

void tedarikci_guncelle(tedarikci yedekTdr[])
{
    FILE *fp;
    int i=0,gNo;
    fp=fopen("Tedarikci.txt","r");
    printf("Guncellenecek tedarikcinin No sunu giriniz:");
    scanf("%d",&gNo);
    while(!feof(fp))
    {
        fscanf(fp,"%d %s %s %s",&yedekTdr[i].no,&yedekTdr[i].ad,&yedekTdr[i].adres,&yedekTdr[i].shr.ad);
        if(yedekTdr[i].no==gNo)
        {
            printf("Tedarikci No:");
            scanf("%d",&yedekTdr[i].no);
            printf("Tedarikci Ad:");
            scanf("%s",&yedekTdr[i].ad);
            printf("Tedarikci Adres:");
            scanf("%s",&yedekTdr[i].adres);
            printf("Tedarikci Sehir:");
            scanf("%s",&yedekTdr[i].shr.ad);
        }

        i++;
    }
    fclose(fp);
    fp=fopen("Tedarikci.txt","w");
    for(int a=0; a<(i-1); a++)
    {
        fprintf(fp,"%d %s %s %s\n\n",yedekTdr[a].no,yedekTdr[a].ad,yedekTdr[a].adres,yedekTdr[a].shr.ad);
    }
    fclose(fp);
}

void tedarikci_listele()
{
    FILE *fp;
    fp=fopen("Tedarikci.txt","r");
    while(!feof(fp))
    {

        fputchar(fgetc(fp));
    }
    printf("\n");
    fclose(fp);
}

void tedarikci_sil(tedarikci yedekTdr[])
{
    FILE *fp=fopen("Tedarikci.txt","r");
    int i=0,a=0,k=0,l=0;
    int tdNo;
    if(fp==NULL)
    {
        printf("Dosya Acilmadi");
    }
    printf("Silinecek Tedarikci No: ");
    scanf("%d",&tdNo);

    while(!feof(fp))
    {
        fscanf(fp,"%d %s %s %s",&yedekTdr[i].no,&yedekTdr[i].ad,&yedekTdr[i].adres,&yedekTdr[i].shr.ad);
        if(yedekTdr[i].no==tdNo)
        {
            l=i;
            k++;
        }
        i++;
    }

    fclose(fp);
    fp = fopen("Tedarikci.txt","w");
    for(a=0; a<(i-1); a++)
    {
        if(yedekTdr[a].no==yedekTdr[l].no)
        {
            strcpy(yedekTdr[a].ad,yedekTdr[a+1].ad);
            strcpy(yedekTdr[a].adres,yedekTdr[a+1].adres);
            yedekTdr[a].no = yedekTdr[a+1].no;
            strcpy(yedekTdr[a].shr.ad,yedekTdr[a+1].shr.ad);
        }
    }
    if(k<=0)
    {
        printf("\Tedarikci No 0 ' dan Kucuk olamaz!\n");
        return;
    }
    for(a=0; a<(i-2); a++)
    {
        fprintf(fp,"%d %s %s %s\n\n",yedekTdr[a].no,yedekTdr[a].ad,yedekTdr[a].adres,yedekTdr[a].shr.ad);
    }
    fclose(fp);
}

void stok_giris(stok stkYedek[],urun yedekUrun[],int *s)
{
    FILE *fp;
    int i=0, k=0;
    char ch;
    fp=fopen("Stok.txt","r");
    while(feof(fp)==NULL)
    {
        ch=getc(fp);
        if(ch == '\n')
        {
            k++;
        }
        i++;
    }
    //Satir sayisi k+1;
    fclose(fp);

    int n=*s;
    fp=fopen("Stok.txt","a");
    printf("Tedarikci No:");
    scanf("%d",&stkYedek[n].tdrNo);
    printf("Urun Kodu:");
    scanf("%d",&stkYedek[n].urun_kod);
    printf("Alis Miktari:");
    scanf("%d",&stkYedek[n].alis_miktar);
    printf("Alis Fiyat:");
    scanf("%f",&stkYedek[n].alis_fiyat);
    printf("Tarih Gun::");
    scanf("%d",&stkYedek[n].trh.gun);
    printf("Tarih Ay:");
    scanf("%d",&stkYedek[n].trh.ay);
    printf("Tarih Yil:");
    scanf("%d",&stkYedek[n].trh.yil);

    fprintf(fp,"STOKID:%d [Tedarikci No: %d] [Urun Kodu: %d] [Alis Miktar: %d] [Alis Fiyat: %f] [Tarih: %d/%d/%d]\n",k+1,stkYedek[n].tdrNo,stkYedek[n].urun_kod,stkYedek[n].alis_miktar,stkYedek[n].alis_fiyat,stkYedek[n].trh.gun,stkYedek[n].trh.ay,stkYedek[n].trh.yil);
    fclose(fp);

    fp=fopen("Urun.txt","r");
    int p=0;
    while(!feof(fp))
    {
        fscanf(fp,"%d %s %s %f %d",&yedekUrun[p].kodu,&yedekUrun[p].adi,&yedekUrun[p].ktg.ad,&yedekUrun[p].satis_fiyati,&yedekUrun[p].stok_miktari);
        p++;
    }
    fclose(fp);
    fp=fopen("Urun.txt","w");

    for(int a=0;a<(p-1);a++)
    {
        if(stkYedek[n].urun_kod==yedekUrun[a].kodu)
        {
            yedekUrun[a].stok_miktari+=stkYedek[n].alis_miktar;
        }
        fprintf(fp,"%d %s %s %f %d\n\n",yedekUrun[a].kodu,yedekUrun[a].adi,yedekUrun[a].ktg.ad,yedekUrun[a].satis_fiyati,yedekUrun[a].stok_miktari);
    }
    fclose(fp);


}


int main()
{
    urun urunler[50];
    urun yedek_urunler[50];
    urun *ptrUrunler[50];
    int i=0;//Ürün id

    tedarikci tdr[50];
    tedarikci *pTdr[50];
    tedarikci yedekTdr[50];
    int t=0;


    stok stkYedek[100];
    int s=0;





    int secimMenu;
    printf("\n\n        STOK TAKIP OTAMASYONUNA HOSGELDINIZ\n\n");
    printf("\t***********MENU**********\n\n");
AnaMenu:
    printf("\t1-Urun Islemleri\n\n");
    printf("\t2-Tedarikci Islemleri\n\n");
    printf("\t3-Stok Islemleri\n\n");
    printf("\t4-Cikis\n\n");
    printf("\tLutfen secim yapiniz\n\n");
    scanf("%d",&secimMenu);
    switch(secimMenu)
    {
    case 1:
altMenu:
        printf("\t---------URUN ISLEMLERI---------\n\n");
        printf("\t1. Urun Ekle\n\n");
        printf("\t2. Urun Guncelle\n\n");
        printf("\t3. Urun Sil\n\n");
        printf("\t4. Urun Listele\n\n");
        printf("\t\t\tAna menuye donmek icin 5 e basiniz!\n\n");
        printf("\nYapmak istediginiz islemi seciniz.\n");
        scanf("%d",&secimMenu);

        switch(secimMenu)
        {
        case 1:

            printf("\n-------Lutfen Urun bilgilerini belirtildigi gibi giriniz.-------\n");
            printf("Urun Adi:");
            scanf("%s",&urunler[i].adi);
            printf("Urun Kodu:");
            scanf("%d",&urunler[i].kodu);
            printf("\tUrun Kategori Bilgilerini giriniz\n");
            printf("Kategori Adi:");
            scanf("%s",&urunler[i].ktg.ad);
            printf("Kategori Id:");
            scanf("%d",&urunler[i].ktg.id);
            printf("Urun Satis Fiyati:");
            scanf("%f",&urunler[i].satis_fiyati);
            printf("Urun Stok Miktar:");
            scanf("%d",&urunler[i].stok_miktari);
            ptrUrunler[i]=&urunler[i];
            urun_ekle(urunler,yedek_urunler,ptrUrunler,&i);
            i++;
            goto altMenu;
            break;

        case 2:

            printf("\nGuncellemek istediginiz urun kodunu giriniz\n");
            int urunKodu;
            scanf("%d",&urunKodu);
            urun_guncelle(yedek_urunler,urunKodu);
            break;

        case 3:

            printf("URUN SIL\n");
            urun_sil(yedek_urunler);
            goto altMenu;

        case 4:

            urun_listele();

        case 5:

            goto AnaMenu;
        }

    case 2:
altMenu2:
        printf("\n\n\t1.Tedarikci ekle\n\n");
        printf("\t2.Tedarikci Guncelle\n\n");
        printf("\t3.Tedarikci Sil\n\n");
        printf("\t4.Tedarikci Listele\n\n");
        printf("\t\t\tAna menuye donmek icin 5 e basiniz!\n\n");
        printf("\nYapmak istediginiz islemi seciniz.\n");
        scanf("%d",&secimMenu);

        switch(secimMenu)
        {
        case 1:

            printf("---------TEDARIKCI EKLEME---------\n\n");
            printf("Tedarikci Adi:");
            scanf("%s",&tdr[t].ad);
            printf("Tedarikci No:");
            scanf("%d",&tdr[t].no);
            printf("Tedarikci Adres:");
            scanf("%s",&tdr[t].adres);
            printf("Tedarikci Sehir Plakasi:");
            scanf("%d",&tdr[t].shr.plaka);
            printf("Tedarikci Sehir Ad:");
            scanf("%s",&tdr[t].shr.ad);
            pTdr[t]=&tdr[t];
            tedarikci_ekle(tdr,pTdr,&t,yedekTdr);
            t++;
            printf("\n");
            goto altMenu2;
            break;

        case 3:

            printf("---------TEDARIKCI SIL---------\n\n");
            tedarikci_sil(yedekTdr);
            printf("\n");
            goto altMenu2;
            break;

        case 2:

            printf("----------TEDARIKCI GUNCELLE---------\n\n");
            tedarikci_guncelle(yedekTdr);
            printf("\n");
            goto altMenu2;
            break;

        case 4:

            printf("---------TEDARIKCI LISTELE---------\n\n");
            tedarikci_listele();
            printf("\n");
            goto altMenu2;
            break;
        case 5:
            goto altMenu;
            break;
        }



    case 4:
        return 0;


    case 3:
        printf("\t---------STOK ISLEMLERI---------\n\n");
        printf("\t1. Urunleri Goruntule\n\n");
        printf("\t2. Urun Stok Girisi Yap\n\n");
        printf("Secim:");
        scanf("%d",&secimMenu);
        switch(secimMenu)
        {
        case 1:
            urun_listele();
            goto altMenu;
            break;
        case 2:
            printf("\t-----STOK GIRIS-----\n");
            stok_giris(stkYedek,yedek_urunler,&s);
            s++;
            goto altMenu;
            break;

        }
        break;
    }
    return 0;
}

