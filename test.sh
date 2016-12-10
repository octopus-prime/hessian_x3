docker rm -f hessian_x3 &>/dev/null || true
docker run -d -it --name hessian_x3 --privileged octopusprime/test
docker exec hessian_x3 mkdir hessian_x3
docker cp . hessian_x3:/hessian_x3
docker exec hessian_x3 bash -c "
	cd hessian_x3; 
	bjam toolset=$1 debug -j$2
"
docker cp hessian_x3:/hessian_x3/bin .
