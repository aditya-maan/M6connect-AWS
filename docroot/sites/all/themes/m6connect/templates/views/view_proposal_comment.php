<?php 
error_reporting(0);
require_once("../../../../default/settings_dbconn.php");

$dbObject 	=  new dbconn;

$comment_id = $_REQUEST['cmd_id'];
$pro_id = $_REQUEST['pro_id'];
$use_id = $_REQUEST['use_id'];


$sql_comment = $dbObject->query("SELECT * FROM comment where cid =$comment_id", 4) ;
//echo '<pre>'; print_r($sql_comment); echo '</pre>';
$entity_val_id = $sql_comment[0]['uid'];
$comment_subject = $sql_comment[0]['subject'];
$comment_created = $sql_comment[0]['created'];

$sql_first_name = $dbObject->query("SELECT * FROM field_revision_field_first_name where entity_id =$entity_val_id", 4) ;
//echo '<pre>'; print_r($sql_first_name); echo '</pre>';
$first_name = $sql_first_name[0]['field_first_name_value'];

$sql_last_name = $dbObject->query("SELECT * FROM field_revision_field_last_name where entity_id =$entity_val_id", 4) ;
//echo '<pre>'; print_r($sql_last_name); echo '</pre>';
$last_name = $sql_last_name[0]['field_last_name_value'];


$sql_descr = $dbObject->query("SELECT * FROM field_data_comment_body where entity_id =$comment_id", 4) ;
$desc = $sql_descr[0]['comment_body_value'];


//db_select()


$sql_read = $dbObject->query("SELECT * FROM read_unread_message", 4) ;
$read_count = count($sql_read);

	for($i=0; $i < $read_count; $i++)
	{
	$read_cmd = $sql_read[$i]['comment_id'];
	$read_user = $sql_read[$i]['user_id'];
		if(($read_user == $use_id) && ($read_cmd == $comment_id))
			{ $arr[$i] = 'true'; }
		else { $arr[$i] = 'false'; }
	}
	
		if (count(array_unique($arr)) === 1 && end($arr) === 'false') {
		$sql_read_insert =  $dbObject->action_query("INSERT INTO read_unread_message (proposal_id, comment_id, user_id, staus) VALUES ($pro_id, $comment_id, $use_id, '1')", 4);
		}

?>


<ul class="view_msg_list">
<li><label>Message Sent From</label>
	<span class="sub_tlt_list"> <?php echo $first_name." "; echo $last_name;  ?> at <?php echo date('m/d/Y g:i A', $comment_created); ?></span>
</li>  
    <li><label>Subject:</label><p class="sub_txt_la"><?php echo $comment_subject; ?></p></li>
<li><label>Message:</label>
<?php echo nl2br($desc); ?>
</li> 
 <li><label>Attachments:</label>
        <div id="view_pade_wrap" class="view_doc_det">
			<table cellpadding="0" cellspacing="0" border="0">
				<thead>
					<tr>
						<th>Document Name</th>
						<th style="text-align:center;">Type</th>
						<th>Uploaded Date</th>
					</tr>
				</thead>
				<tbody>
				
				<?php
				$sql_img = $dbObject->query("SELECT * FROM field_data_field_image_upload where entity_id =$comment_id", 4) ;
				//echo '<pre>'; print_r($sql_img); echo '</pre>';
				$img_count = count($sql_img);
				if($img_count == '0')
				{
				echo '<tr>
					<td colspan="3" style="text-align:center;">No Proposal Document Sent</td>
					</tr>';
				}
				else
				{
				for($i=0; $i < $img_count; $i++)
				{
				$image_id = $sql_img[$i]['field_image_upload_fid'];
				$sql_img_file = $dbObject->query("SELECT * FROM file_managed where fid =$image_id", 4) ;
				//echo '<pre>'; print_r($sql_img_file); echo '</pre>'; 
				$img_name = $sql_img_file[0]['filename'];			
				$img_time = $sql_img_file[0]['timestamp'];				
				$img_mine = $sql_img_file[0]['filemime'];
				$det_fid = $sql_img_file[0]['fid'];
				
				switch ($img_mine) {
				case "image/jpeg":
				case "image/jpg":
				case "image/png":
				case "image/gif":
				case "image/tif":
					$img_src = "image-x-generic";
					break;					
				case "application/pdf":		
					$img_src = "application-pdf";
					break;				
				case "text/plain":
					$img_src = "text-plain";
					break;	
				case "application/msword":
				case "application/vnd.ms-word.document.macroEnabled.12":
				case "application/vnd.oasis.opendocument.text":
				case "application/vnd.oasis.opendocument.text-template":
				case "application/vnd.oasis.opendocument.text-master":
				case "application/vnd.oasis.opendocument.text-web":
				case "application/vnd.openxmlformats-officedocument.wordprocessingml.document":
				case "application/vnd.stardivision.writer":
				case "application/vnd.sun.xml.writer":
				case "application/vnd.sun.xml.writer.template":
				case "application/vnd.sun.xml.writer.global":
				case "application/vnd.wordperfect":
				case "application/x-abiword":
				case "application/x-applix-word":
				case "application/x-kword":
				case "application/x-kword-crypt":
					$img_src = "x-office-document";
					break;
			   // Spreadsheet document types.
				case "application/vnd.ms-excel":
				case "application/vnd.ms-excel.sheet.macroEnabled.12":
				case "application/vnd.oasis.opendocument.spreadsheet":
				case "application/vnd.oasis.opendocument.spreadsheet-template":
				case "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet":
				case "application/vnd.stardivision.calc":
				case "application/vnd.sun.xml.calc":
				case "application/vnd.sun.xml.calc.template":
				case "application/vnd.lotus-1-2-3":
				case "application/x-applix-spreadsheet":
				case "application/x-gnumeric":
				case "application/x-kspread":
				case "application/x-kspread-crypt":
				  $img_src = "x-office-spreadsheet";
				  break;

				// Presentation document types.
				case "application/vnd.ms-powerpoint":
				case "application/vnd.ms-powerpoint.presentation.macroEnabled.12":
				case "application/vnd.oasis.opendocument.presentation":
				case "application/vnd.oasis.opendocument.presentation-template":
				case "application/vnd.openxmlformats-officedocument.presentationml.presentation":
				case "application/vnd.stardivision.impress":
				case "application/vnd.sun.xml.impress":
				case "application/vnd.sun.xml.impress.template":
				case "application/x-kpresenter":
				  $img_src = "x-office-presentation";
				  break;

				// Compressed archive types.
				case "application/zip":
				case "application/x-zip":
				case "application/stuffit":
				case "application/x-stuffit":
				case "application/x-7z-compressed":
				case "application/x-ace":
				case "application/x-arj":
				case "application/x-bzip":
				case "application/x-bzip-compressed-tar":
				case "application/x-compress":
				case "application/x-compressed-tar":
				case "application/x-cpio-compressed":
				case "application/x-deb":
				case "application/x-gzip":
				case "application/x-java-archive":
				case "application/x-lha":
				case "application/x-lhz":
				case "application/x-lzop":
				case "application/x-rar":
				case "application/x-rpm":
				case "application/x-tzo":
				case "application/x-tar":
				case "application/x-tarz":
				case "application/x-tgz":
				  $img_src = "package-x-generic";
				  break;

				// Script file types.
				case "application/ecmascript":
				case "application/javascript":
				case "application/mathematica":
				case "application/vnd.mozilla.xul+xml":
				case "application/x-asp":
				case "application/x-awk":
				case "application/x-cgi":
				case "application/x-csh":
				case "application/x-m4":
				case "application/x-perl":
				case "application/x-php":
				case "application/x-ruby":
				case "application/x-shellscript":
				case "text/vnd.wap.wmlscript":
				case "text/x-emacs-lisp":
				case "text/x-haskell":
				case "text/x-literate-haskell":
				case "text/x-lua":
				case "text/x-makefile":
				case "text/x-matlab":
				case "text/x-python":
				case "text/x-sql":
				case "text/x-tcl":
				  $img_src = "text-x-script";
				  break;
				// HTML aliases.
				case "application/xhtml+xml":
				  $img_src = "text-html";
				  break;
				// Executable types.
				case "application/x-macbinary":
				case "application/x-ms-dos-executable":
				case "application/x-pef-executable":
				  $img_src = "application-x-executable";
				  break;
				default:
				  $img_src = "application-octet-stream";
				}	
					
				?>
				<tr>
				<td><a style="pointer-events: none;" id="read_down_doc_<?php echo $i; ?>" href="<?php echo $img_name; ?>" data="<?php echo $det_fid;?>" class="cust-propsal-link proposal-comunication-attachment"><?php echo $img_name; ?></a></td>
				<td align="center"><img src ="/modules/file/icons/<?php echo $img_src; ?>.png"></td>
				<td><span><?php echo date('m/d/Y g:i A', $img_time); ?></span></td>					
				</tr>
				<?php } } ?>
				
					
						
					
				</tbody>
			</table>					
		</div>
		
		<?php	if($img_count > 0)	{ ?>
		<div class="m6_download">
		<button id="download-btn-msg" class="m6_down_all" >Download All Documents</button>
		<div id="down_all_test_msg" style="display:none;"></div>
		</div>
		 <?php } ?>
		
</li> 
</ul>
 <script>
 var url_det = [];

	$('#download-btn-msg').click(function(){
	$leng = $('#view_pade_wrap.view_doc_det table tbody tr').length;
	var param= new Array();
	var doc =0;	
	for(var i=0; i<$leng; i++)
    {
	  var val_id = $("#read_down_doc_"+ i).attr('href');
      url_det[i] = val_id;
	  doc++;
	  param.push('fids[]=' + $("#read_down_doc_" + i).attr('data') || 0);
	}
	var url = param.join('&');
	if(doc > 0 && url!=''){
	   url = '/all-document-download?'+url;
	   window.location = url;
	}
	/*$.ajax({							
		type: 'POST',
		url: 'http://dev-m6connect.pantheon.io/sites/default/download_all.php',
		data: { url_down: url_det },
		dataType: "html",
		success: function(content) {
		$('#down_all_test_msg').html('<iframe src="'+ content +'"></iframe>');  // replace								   
		}
	});*/
	});
	$('.cust-propsal-link').click(function(e){
		e.preventDefault();
	});
</script>
