<div class="my-form-wrapper">
  <?php 
  //pre($form,1);
		print '<div class="org-first-wrapper">';
		print render ($form['title']);
		//print render ($form['field_org_name']);
		print render ($form['field_owner_name']);
		print render ($form['field_legal_name']);
		print render ($form['field_legal_structure']);
		print render ($form['field_incorporated_country']);
		print render ($form['field_incorporated_state']);
		print render ($form['field_taxpayer_ssn_ein']);
		print render ($form['field_duns_number']);
		print render ($form['field_cage_code']);
		print render ($form['field_description']);
		print render ($form['field_service_description']); 
		print drupal_render($form['field_keywords']);
        print drupal_render($form['field_facilities_construction']);
        print render($form['field_regions']);
		
        print drupal_render($form['field_industry_naics']);
		print drupal_render($form['field_industry_naicss']);
        print render($form['field_products_service_unspsc']);
		print '<div style="display:none;">';
        
		print '</div>';
        print drupal_render($form['field_projects']);
		
		
		
		
        /*print drupal_render($form['field_diversity_credential']); */
		
		print '</div>';
  
        
        print '<div class="org-second-wrapper">';
		print render ($form['field_number_employees']);
		print render ($form['field_annual_revenue']);
		print render ($form['field_year_founded']);
		print render ($form['field_website']);
		print render ($form['field_org_address']);
		print render ($form['field_org_phone']);
		print render ($form['field_org_fax']);
		print render ($form['field_company_email']);
		        
		print '</div>';
        
        
        print '<div class="org-third-wrapper">';
		print render ($form['field_logo']);
		print '</div>';
        
       /* print '<div class="org-fifth-wrapper">';
		print render ($form['group_government_certifications']);
        print render($form['field_8_a_certificate_file']);
		print '</div>';*/
		
		print '<div class="org-sixth-wrapper">';
		print render($form['field_diversity_credentials']);
		//print render($form['credential_contents']);
		
		$query = db_select('node', 'n');
		$query->fields('n', array('nid'));
		$query->condition('n.type', 'diversity', '=');
        $result = $query->execute()->fetchAll();
		if($result) {
	      foreach ($result as $qry) {
            $dnid = $qry->nid;
			print drupal_render($form['custwrap'.$dnid]);
		
		  }
		}
		print '</div>';
		if(!(array_key_exists(3, $user->roles) && array_key_exists(6, $user->roles))) {
		print '<div class="cust-hiddenfield-wrapper" style="display:none;">';
		}
		print render($form['field_company_type']);
		if(!(array_key_exists(3, $user->roles) && array_key_exists(6, $user->roles))) {
		print '</div>';
		}
		
		print '<div class="cust-field org-fourth-wrapper">';
		print render($form['group_register']);
		
		print render($form['form_build_id']);
        print render($form['form_id']);
        print render($form['form_token']);
		print drupal_render_children($form); 
		print render($form['#validate']);
		print '</div>'; 
        
       /* print '<div class="org-fourth-wrapper">';
		print render($form['form_build_id']);
        print render($form['form_id']);
        print render($form['form_token']);
        print '<div class="form-actions">';
        print render($form['actions']['submit']);
        print '</div>';
        print render($form['#validate']);
		print '</div>'; */
		
		
  
  ?>
</div>