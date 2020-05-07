void N01hist(){

	TH1F *h1 = new TH1F("h1","title",10,0,10);
	
	for(int i=0; i<10; i++){
	
		if(i<3){
			h1->Fill(1);
		}else{
			h1->Fill(3);
		}
	}

	h1->Draw();


}
