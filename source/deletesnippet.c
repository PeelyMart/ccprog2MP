int delete(struct BattlePet d[], int index){
  int i;
  int nConfirm;
  printf("This will delete the battle pet for ALL USERS confirm?\n");
  printf("\t\t[0]Confirm\t\t[1]Exit\n");
  scanf("%d", &nConfirm);
  if(nConfirm == 0){
    
    for(i = index; i < MAX_PETS-1; i++){
      d[i] = d[i+1];
    }
  }
  
}
