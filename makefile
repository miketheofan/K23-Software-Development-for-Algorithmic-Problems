# push_first:
# 	git init
# 	git add .
# 	echo "Commit message: "
# 	read Message
# 	git commit -m $(Message)
# 	git branch -M main
# 	git remote add origin https://github.com/miketheofan/Software-Development-for-Algorithmic-Problems.git
# 	git push -u origin main
# 	git pull origin main

push:
	@git init
	@git add .
	@read -p "Message: " Message; \
	git commit -m $$Message
	@git push -u origin main
	@git pull origin main
