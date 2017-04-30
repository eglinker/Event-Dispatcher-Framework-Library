<html>
 <head>
  <title>PHP Test</title>
 </head>
 <body>
 <h1>
	<?php echo '<p>Control Panel</p>'; ?> 
 </h1>
 
 
 <?php
    $sock = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP);

   //$msg = "GPIORISE5";
    $msg = $_POST[submit];
    $len = strlen($msg);

    socket_sendto($sock, $msg, $len, 0, '127.0.0.1', 8888);
    socket_close($sock);
?>
 

<form action="index.php" method="post">
    <table border="1" width="100%">
        <tr>
			<td align="center" width="25%" height = 80 style="font-size: 25px;">
				<p><input type="submit" style="width:80%; height:100%;font-size:22px;"  name="submit"  value="LED TOGGLE"></p>
			</td>
			<td  width="50%"> Toggle LED connected to GPIO6.</td>
			
						
		</tr>  
        <tr>
			<td align="center" width="25%" height = 80 style="font-size: 25px;">
				<p><input type="submit" style="width:80%; height:100%;font-size:22px;"  name="submit"  value="LED ON"></p>
			</td>
			<td> Turn on LED connected to GPIO6. </td>
			
			
		</tr>  
        <tr>
			<td align="center" width="25%" height = 80 style="font-size: 25px;">
				<p><input type="submit" style="width:80%; height:100%;font-size:22px;"  name="submit"  value="LED OFF"></p>
			</td>
			<td> Turn off LED connected to GPIO6.</td>
			
			
		</tr>  
        <tr>
			<td align="center" width="25%" height = 80 style="font-size: 25px;">
				<p><input type="submit" style="width:80%; height:100%;font-size:22px;"  name="submit"  value="GPIORISE5"></p>
			</td>
			<td> Toggle LED connected to GPIO6 by faking a pushbutton event at GPIO5.</td>
						
		</tr>  
	    
		<tr>
			<td align="center" width="25%" height = 80 style="font-size: 25px;">
				<p><input type="submit" style="width:80%; height:100%;font-size:22px;"  name="submit"  value="PLAY MUSIC"></p>
			</td>
			<td> Start up ffplay with an mp3.</td>
						
		</tr>  
		
		<tr>
			<td align="center" width="25%" height = 80 style="font-size: 25px;">
				<p><input type="submit" style="width:80%; height:100%;font-size:22px;"  name="submit"  value="STOP MUSIC"></p>
			</td>
			<td> </td>
						
		</tr>  

    
	</table>
</form>
 
 
 
 </body>
</html>