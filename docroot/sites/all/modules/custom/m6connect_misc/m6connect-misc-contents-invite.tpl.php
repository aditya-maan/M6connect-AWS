<?php

global $user, $base_url;
//$NodeCompNid = _get_user_company_nid($user->uid);
 
if(!empty(arg(3)) && is_numeric(arg(3))){
  $company = node_load(arg(3));
  $companyNid = $company->nid;
  $account = $company;
 }

$userRoles = $user->roles;
$userRoleskey = array_keys($userRoles);
$rolesArray = array(7, 8, 9, 4);
//print_r($userRoleskey);
$userplan = array_intersect($rolesArray, $userRoleskey);
foreach ($userplan as $key => $value) {
    $planid = $value;
}
?>

<div class="clearfix">
	<h3 class="invite-user">
<!--            <strong>Company Name </strong>-->
                <?php echo $account->title ?></h3>
	<div><strong>Membership Level: </strong><?php $userRoles[$planid];
                $arr = explode(' ',trim($userRoles[$planid]));
echo $arr[0];
                ?></div>
	<br />
	<p><a href="/upgrade-your-membership-subscription">Upgrade Membership</a></p>
	<hr/>
	<h3 class="invite-user"><strong>Invite User</strong></h3>
	<p>You can Invite Multiple people to join your m6connect company account by entering their email addresses below. An email will be sent to each address
		with a spacial invitation code  that will add these users to your company once they register. </p>
	<p> You can also select a default role  for each new user before you invite them. once registered, the user  will automatically be given the role that you choose. </p>
</div>
<?php
$indexarray = array(5, 12, 41, 46);
$userRoles = user_roles();
$count = count($indexarray);
$displayRoles = array();

for ($i = 0; $i < $count; $i++) {

    $options .= '<option value="' . $indexarray[$i] . '">' . $userRoles[$indexarray[$i]] . '</option>';
}
?>
<form action="" method="post" id="send_invitation">
	<table class="table table-striped">
		<thead>
			<tr>
				<th> Email Address </th>
				<th> Default Role </th>
			</tr>
		</thead>
		<tbody>
			<tr>
				<td>
					<input type="text" name="email[]" id="email_1" placeholder="Email" style="border: 2px solid #eee;height: 32px;width: 100%;" />
				</td>
				<td>
					<select name="role[]" id="role_1">
						<option value="0">--Select Role for User--</option>
						<?php echo $options; ?>
					</select>
				</td>
			</tr>
			<tr>
				<td>
					<input type="text" name="email[]" id="email_2" placeholder="Email" style="border: 2px solid #eee;height: 32px;width: 100%;" />
				</td>
				<td>
					<select name="role[]" id="role_2">
						<option value="0">--Select Role for User--</option>
						<?php echo $options; ?>
					</select>
				</td>
			</tr>
			<tr>
				<td>
					<input type="text" name="email[]" id="email_3" placeholder="Email" style="border: 2px solid #eee;height: 32px;width: 100%;" />
				</td>
				<td>
					<select name="role[]" id="role_3">
						<option value="0">--Select Role for User--</option>
						<?php echo $options; ?>
					</select>
				</td>
			</tr>
			<tr>
				<td>
					<input type="text" name="email[]" id="email_4" placeholder="Email" style="border: 2px solid #eee;height: 32px;width: 100%;" />
				</td>
				<td>
					<select name="role[]" id="role_4">
						<option value="0">--Select Role for User--</option>
						<?php echo $options; ?>
					</select>
				</td>
			</tr>
			<tr>
				<td>
					<input type="text" name="email[]" id="email_5" placeholder="Email" style="border: 2px solid #eee;height: 32px;width: 100%;" />
				</td>
				<td>
					<select name="role[]" id="role_5">
						<option value="0">--Select Role for User--</option>
						<?php echo $options; ?>
					</select>
				</td>
			</tr>
			<tr>
				<td>
					<input type="text" name="email[]" id="email_6" placeholder="Email" style="border: 2px solid #eee;height: 32px;width: 100%;" />
				</td>
				<td>
					<select name="role[]" id="role_6">
						<option value="0">--Select Role for User--</option>
						<?php echo $options; ?>
					</select>
				</td>
			</tr>
			<tr>
				<td>
					<input type="text" name="email[]" id="email_7" placeholder="Email" style="border: 2px solid #eee;height: 32px;width: 100%;" />
				</td>
				<td>
					<select name="role[]" id="role_7">
						<option value="0">--Select Role for User--</option>
						<?php echo $options; ?>
					</select>
				</td>
			</tr>
			<tr>
				<td>
					<input type="text" name="email[]" id="email_8" placeholder="Email" style="border: 2px solid #eee;height: 32px;width: 100%;" />
				</td>
				<td>
					<select name="role[]" id="role_8">
						<option value="0">--Select Role for User--</option>
						<?php echo $options; ?>
					</select>
				</td>
			</tr>
			<tr>
				<td>
					<input type="text" name="email[]" id="email_9" placeholder="Email" style="border: 2px solid #eee;height: 32px;width: 100%;" />
				</td>
				<td>
					<select name="role[]" id="role_9">
						<option value="0">--Select Role for User--</option>
						<?php echo $options; ?>
					</select>
				</td>
			</tr>
		</tbody>
	</table>
    <input type="hidden" name="companyNid" value="<?php echo $companyNid; ?>" id="companyNid"/>
    
    <div class="text-left"> <a href="javascript:" class="btn btn-primary form-submit" onclick="send_invitation()">Send Invitation To Join</a> <a class="cancel-button" href="javascript:" onclick="window.location.href = '<?php echo $base_url.'/people/member/'.$companyNid.'' ?>'">Cancel</a> </div>
</form>
<script>
    function send_invitation() {
            if(validateform()){
                jQuery.post('/people/invite/users/submit', jQuery('#send_invitation').serialize(),function(data){
                    //alert(data);
                    window.location.href = '<?php echo $base_url.'/people/member/'.$companyNid.'' ?>';
                })
            }
    }
    function validateform() {
        var check_mail_exist = false;
        jQuery('[id^=email_]').each(function () {
            if (this.value != '') {
                
                if(!validateEmail(this.value)){
                    this.style.border = '1px solid red';
                    check_mail_exist = false;
                    return false;
                }else{
                    check_mail_exist = true;
                }
                this.style.border = '2px solid #eee';
                ids = this.id;
                idssplit = ids.split("_");
                if(jQuery('#role_'+idssplit[1]).val() == 0){
                    jQuery('#role_'+idssplit[1]).css('border', '1px solid red');
                    check_mail_exist = false;
                    return false;
                }else{
                    check_mail_exist = true;
                }
                jQuery('#role_'+idssplit[1]).css('border', '1px solid #eee');
            }
        });
        return check_mail_exist;
    }
    function validateEmail($email) {
        var emailReg = /^([\w-\.]+@([\w-]+\.)+[\w-]{2,4})?$/;
        return emailReg.test($email);
    }
</script>