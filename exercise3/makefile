out1:
	@python3 forecast/forecast.py -d nasdaq2007_17.csv -n 3

out1train:
	@python3 forecast/train_forecast.py -d nasdaq2007_17.csv

out2:
	@python3 detect/detect.py -d nasdaq2007_17.csv -n 3 -mae 3.0

out2train:
	@python3 detect/train_detect.py -d nasdaq2007_17.csv	

out3:		
	@python3 reduce/reduce.py -d nasdaq2007_17.csv -q nasdaq2007_17.csv -od reduce/dataset.csv -oq reduce/query.csv

out3train:
	@python3 reduce/train_reduce.py -d nasdaq2007_17.csv		