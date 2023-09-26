import argparse

def multi(n):
	for i in range(n):
		num = i * i+1

if __name__ == "__main__":
	parser = argparse.ArgumentParser(description="Preform varius sizes of multiplication")
	parser.add_argument("count", type=int, help="Number of times to multiply")
	args = parser.parse_args()
    
	if args.count == 100000:
  		multi(100000)
  		multi(100000)
  		multi(100000)
  		multi(100000)   
  		multi(100000)
  		multi(100000) 
	if args.count == 200000:
  		multi(200000)
  		multi(200000)
  		multi(200000)
	if args.count == 300000:
    		multi(300000)
    		multi(300000)
	if args.count == 600000:
    		multi(600000)
