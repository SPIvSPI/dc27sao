#!/usr/bin/env bash

FWDIR_W=whitefw
FWDIR_B=blackfw
PORT=COM21

cat <<EOF
      ___           ___                                  ___           ___               
     /  /\         /  /\      ___           ___         /  /\         /  /\      ___     
    /  /:/_       /  /::\    /  /\         /__/\       /  /:/_       /  /::\    /  /\    
   /  /:/ /\     /  /:/\:\  /  /:/         \  \:\     /  /:/ /\     /  /:/\:\  /  /:/    
  /  /:/ /::\   /  /:/~/:/ /__/::\          \  \:\   /  /:/ /::\   /  /:/~/:/ /__/::\    
 /__/:/ /:/\:\ /__/:/ /:/  \__\/\:\__   ___  \__\:\ /__/:/ /:/\:\ /__/:/ /:/  \__\/\:\__ 
 \  \:\/:/~/:/ \  \:\/:/      \  \:\/\ /__/\ |  |:| \  \:\/:/~/:/ \  \:\/:/      \  \:\/\ 
  \  \::/ /:/   \  \::/        \__\::/ \  \:\|  |:|  \  \::/ /:/   \  \::/        \__\::/
   \__\/ /:/     \  \:\        /__/:/   \  \:\__|:|   \__\/ /:/     \  \:\        /__/:/ 
     /__/:/       \  \:\       \__\/     \__\::::/      /__/:/       \  \:\       \__\/  
     \__\/         \__\/                     ~~~~       \__\/         \__\/              

         ------=========={ SPIvSPI Firmware Loader v0.fuck }==========-------

EOF

FILES_W=`ls $FWDIR_W`
PRETTYFILES_W=`ls $FWDIR_W | sed 's/^/ - /'`
FILES_B=`ls $FWDIR_B`
PRETTYFILES_B=`ls $FWDIR_B | sed 's/^/ - /'`

echo "About to program these files in rotation:"
echo "$PRETTYFILES_W"
echo "$PRETTYFILES_B"
echo

RUNNING=1
PROGRAMMED=0
FAILED=0

while (( RUNNING == 1 )) ; do
	for FW in $FILES_W ; do
		echo -e "\nNext up: $FW"
		read -p "Q to quit, S to skip, enter to program:" -n1 IN
		if [[ "$IN" == "S" ]] ; then continue ; fi
		if [[ "$IN" == "Q" || "$IN" == "q" ]] ; then
			echo -e "\n\nQuitting!"
			RUNNING=0
			break
		fi
		OUT=`./efm8load.exe -p $PORT -t $FWDIR_W/$FW`
		if echo "$OUT" | fgrep '[ 0 ] errors' - ; then
			((PROGRAMMED++))
			echo "$OUT"
			echo
			echo "Programmed $PROGRAMMED good so far"
		else
			((FAILED++))
			echo
			cat <<-EOF
				    ###   #   ###  #   
				    #    # #   #   #   
				    ##   ###   #   #   
				    #    # #   #   #   
				    #    # #  ###  ### 

			EOF
			echo "$OUT"
			echo
			echo "Failed $FAILED so far"
		fi
	done
	if (( $RUNNING == 0 )) ; then break ; fi
	for FW in $FILES_B ; do
		echo -e "\nNext up: $FW"
		read -p "Q to quit, S to skip, enter to program:" -n1 IN
		if [[ "$IN" == "S" ]] ; then continue ; fi
		if [[ "$IN" == "Q" || "$IN" == "q" ]] ; then
			echo -e "\n\nQuitting!"
			RUNNING=0
			break
		fi
		OUT=`./efm8load.exe -p $PORT -t $FWDIR_B/$FW`
		if echo "$OUT" | fgrep '[ 0 ] errors' - ; then
			((PROGRAMMED++))
			echo "$OUT"
			echo
			echo "Programmed $PROGRAMMED good so far"
		else
			((FAILED++))
			echo
			cat <<-EOF
				    ###   #   ###  #   
				    #    # #   #   #   
				    ##   ###   #   #   
				    #    # #   #   #   
				    #    # #  ###  ### 

			EOF
			echo "$OUT"
			echo
			echo "Failed $FAILED so far"
		fi
	done
done

echo
echo "Programming summary"
echo "-------------------"
echo "  GOOD: $PROGRAMMED"
echo "  FAIL: $FAILED"
echo
echo "SPIvSPI Firmware Loader run complete."
echo
