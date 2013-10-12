sed -i '/\PM/d' $1
sed -i '/\TV/d' $1


sed 's/Picks//g'  $1



sed -i 's/½/\.5/g' $1


sed -i 's/PK/\-0.0001/g' $1



sed -i 's/u/\ /g' $1
