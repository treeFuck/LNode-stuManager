#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// ����ѧ���ṹ��
typedef struct LNode { 
	int stu_id; // ѧ��ѧ��
	int grade;  // �꼶
	int _class; // �༶
	int sex;  // �Ա�
	char name[30]; // ����
  	struct LNode *next; 
} LNode, *LinkedList;



/*
  �����ú�����
*/

// 1. ��������
int inputInt() {
	int a, result;
	fflush(stdin);
	a = scanf("%d",&result);
	if(a == 0)
	{
		printf("\n���������֡������������������: ");
        result = inputInt();
	}
	return result;
}




/*
  ����ʼ����
*/

// 2. ��ʼ��ѧ������
void init(LinkedList &link) {
	link = (LinkedList)malloc(sizeof(LNode));
	link->next = NULL;
}



/*
  ������һ��ѧ����
*/

// 3. �ж�ѧ��Ϊstu_id��ѧ���Ƿ����
LinkedList ifStuExist(LinkedList &link, int stu_id) {
	LinkedList p;
	LinkedList result = NULL;
	for(p = link->next; p != NULL; p=p->next) {
		if(p->stu_id == stu_id) {
			result = p;
			break;
		}
	}
	return result;
}
// 4. ��ӡһ��ѧ��
void printfStu(LinkedList p) {
	printf("\n  %s( %d )  [%s]   %d �꼶 %d ��\n", p->name, p->stu_id, p->sex==0?"��":"Ů", p->grade, p->_class);
}
// 5. ����ѧ���������ܺ�����
void searchStu(LinkedList link) {
	printf("\n�����ҡ�������Ҫ���ҵ�ѧ��: ");
	int stu_id = inputInt();
	LinkedList p = ifStuExist(link, stu_id);
	if(p == NULL) {
		printf("\n�����ҡ�������ѧ��Ϊ %d ��ѧ��: ", stu_id);
	} else {
		printf("\n�����ҳɹ���: \n");
		printfStu(p);
		
	}
}




/*
  ������һ��ѧ����
*/

// 6. ���������ڵ�
LinkedList addLNode(LinkedList &link, int stu_id, int grade, int _class, int sex, char *name) {

	LinkedList p = (LinkedList)malloc(sizeof(LNode));
	// ��������
	p->stu_id = stu_id;
	p->grade = grade;
	p->_class = _class;
	p->sex = sex;
	strcpy(p->name, name);

	// ���ڵ�Ž������ĵ�һ���ڵ�
	p->next = link->next;
	link->next = p;	
	return p;
}

// 7. ����ѧ��
int inputStuId(LinkedList &link) {
	int stu_id = inputInt();
	if(ifStuExist(link, stu_id) != NULL) { 
		// ���ú���ifStuExist��ѧ��id����
		printf("\n���������ѧ��Ϊ %d ��ѧ���Ѿ����ڣ�����������: ", stu_id);
        stu_id = inputStuId(link);
	}
	return stu_id;
}

// 8. �����µ�ѧ���������ܺ�����
void add(LinkedList &link) {
	int stu_id;
	int grade;
	int _class;
	int sex;
	char name[30];
	printf("\n  �����ӡ�����[ѧ��](int)��");
	stu_id = inputStuId(link);
	LinkedList p;

	printf("\n  �����ӡ�����[�꼶](int)��");
	grade = inputInt();

	printf("\n  �����ӡ�����[���](int)��");
	_class = inputInt();

	printf("\n  �����ӡ�����[�Ա�](int, ���� 0 Ϊ���ԣ���������ΪŮ��)��");
	sex = inputInt();

	printf("\n  �����ӡ�����[����](char *)��");
	fflush(stdin);
	gets(name);
	
	p = addLNode(link, stu_id, grade, _class, sex, name);
	printf("\n �����ӡ� �ɹ�����ѧ����\n");
	printfStu(p);
}




/*
  ��ɾ��һ��ѧ����
*/

// 9. ����ѧ��Ϊstu_id��ѧ���ڵ�ĸ��ڵ�
LinkedList searchFather(LinkedList &link, int stu_id) {
	LinkedList p;
	LinkedList result = NULL;
	for(p = link; p->next != NULL; p=p->next) {
		if(p->next->stu_id == stu_id) {
			result = p;
			break;
		}
	}
	return result;
}

// 9.ɾ�������ڵ�
void delNode(LinkedList &link, LinkedList fp) {
	LinkedList temp = fp->next;
	fp->next = temp->next;
	free(temp);
}

// 10.ɾ��һ��ѧ���������ܺ�����
void del(LinkedList &link) {
	printf("\n��ɾ����������Ҫɾ����ѧ��id:  ");
	int stu_id = inputInt();
	LinkedList fp = searchFather(link, stu_id);
	
	if(fp == NULL) {
		printf("\n��ɾ��ʧ�ܡ�������ѧ��Ϊ %d ��ѧ�� ", stu_id);
	} else {
		delNode(link, fp);
		printf("\n��ɾ�����ɹ�ɾ��ѧ��( %d): ", stu_id);
	}
}




/*
  ���޸�һ��ѧ������Ϣ��
*/

// 11. ѡ�����
int chooseWay() {
	int way = inputInt();
	if(way < 0 || way > 3) { 
		printf("\n���������������0-3֮������֣�����������: ");
        way = chooseWay();
	}
	return way;
}
// 12. �޸�����
void changeData(LinkedList p, int way) {
	if(way == 0) {
		printf("\n���޸ġ�����(char *):  ");
		fflush(stdin);
		gets(p->name);
	} else if(way == 1) {
		printf("\n���޸ġ��Ա�(int, ���� 0 Ϊ���ԣ���������ΪŮ��)����:  ");
		p->sex = inputInt();
	} else if(way == 2) {
		printf("\n���޸ġ��꼶(int):  ");
		p->grade = inputInt();
	} else if(way == 3) {
		printf("\n���޸ġ����(int):  ");
		p->_class = inputInt();
	}
}
// 13. �޸�
void change(LinkedList &link) {
	printf("\n���޸ġ�������Ҫ�޸���Ϣ��ѧ����ѧ��id:  ");
	int stu_id = inputInt();
	LinkedList p = ifStuExist(link, stu_id);
	if(p == NULL) {
		printf("\n���޸ġ�������ѧ��Ϊ %d ��ѧ��: ", stu_id);
	} else {
		printf("\n���޸ġ�ѡ���޸��ĸ���Ϣ��0->������1->�Ա�2->�꼶��3->�༶����");
		int way = chooseWay();
		changeData(p, way);
		
	}
}




/*
  ����ӡȫ��ѧ����
*/

// 14. ��ӡȫ��ѧ��
void printfALL(LinkedList &link) {
	LinkedList p;
	if(link->next == NULL) {
		printf("\n ����ӡ�� ����ѧ����Ϣ");
		return;
	}
	for(p = link->next; p != NULL; p = p->next) {
		printfStu(p);
	}
}



/*
  ���ļ���д������
*/

// 15. ��ȡ�ļ���������
void readFile(LinkedList link) {
	FILE * fp;
	LNode p;
	int num = 0;
	if( (fp=fopen("myfile.txt","rb")) == NULL) {
		printf("\n\n �����ݶ�ȡ������ ���ڳ���ͬ��Ŀ¼���½�һ��myfile.txt�ļ� ");
		getchar();
		exit(0);
	}
	while(fread(&p, sizeof(LNode), 1, fp) == 1)   //����������ݣ�����ʾ�������˳�
	{	
		 // printfStu(&p);
		num++;
		 addLNode(link, p.stu_id, p.grade, p._class, p.sex, p.name); 
	}
	printf("\n ����ȡ���ݡ� �� myfile.txt �ɹ���ȡ��[ %d ]��ѧ����Ϣ \n", num);
}

// 16. ������д���ļ�
void writeFile(LinkedList link) {
	FILE * fp;
	LinkedList p;
	fp = fopen ("myfile.txt", "wb");
	if(fp == NULL) {
		return;
	}
	for(p = link->next; p != NULL; p = p->next) {
		fwrite(p, sizeof(LNode), 1, fp);
	}
	
	fclose (fp);
}

/*
  ����������
*/

// ���ܱ�
void menu()
{
	
	printf("\n\n                    **��ѡ�����¹���**\n\n");
	printf("     |������������������������  &&   ���ܡ�������������������������|\n");
	printf("     |-������������������������������������������������������������|\n");
	printf("     |---------------------1    TO   [����]һ��ѧ��----------------|\n");
	printf("     |-������������������������������������������������������������|\n");
	printf("     |---------------------2    TO   [ɾ��]һ��ѧ��----------------|\n");
	printf("     |-������������������������������������������������������������|\n");
	printf("     |---------------------3    TO   [����]ѧ����Ϣ----------------|\n");
	printf("     |-������������������������������������������������������������|\n");
	printf("     |---------------------4    TO   [�޸�]ѧ����Ϣ----------------|\n");
	printf("     |-������������������������������������������������������������|\n");
	printf("     |---------------------5    TO   [��ӡ]ȫ��ѧ��----------------|\n");
	printf("     |-������������������������������������������������������������|\n");
	printf("     |---------------------6    TO   [�˳�]------------------------|\n");
	printf("     |-������������������������������������������������������������|\n");
	printf("     |-������������������������������������������������������������|\n");
}


// �򻯽���
void reactive()
{
	printf("\n\n");
	system("PAUSE");
	system("cls");
	menu();
	printf("\n��ѡ�����������: ");
}

// ������
void main()
{	
	int i;
	LinkedList stu;
	
	init(stu);
	readFile(stu);

	menu();
	printf("\n��ѡ�����������: ");
    while((i = inputInt()) != 6)
	{	
		if(1 <= i && i <= 5)
		{	
			switch(i)
			{
				case 1:
					// [����]һ��ѧ��
					add(stu);
					writeFile(stu);
					reactive();
					break;
				case 2:
					// [ɾ��]һ��ѧ��
					del(stu);
					writeFile(stu);
					reactive();
					break;
				case 3:
					// [����]ѧ����Ϣ
					searchStu(stu);
					reactive();
					break;
				case 4:
					// [�޸�]ѧ����Ϣ
					change(stu);
					reactive();
					break;
				case 5:
					// [��ӡ]ȫ��ѧ��
					printfALL(stu);
					reactive();
					break;
			}
		}
		else 
			printf("\n��ѡ�������ѡ����������,������ѡ��:  ");
	}
	printf("\n\n�������������Ѿ���������л����ʹ�ã�\n\n");
}