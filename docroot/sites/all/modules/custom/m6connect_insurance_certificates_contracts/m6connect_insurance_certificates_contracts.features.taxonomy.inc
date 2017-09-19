<?php
/**
 * @file
 * m6connect_insurance_certificates_contracts.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function m6connect_insurance_certificates_contracts_taxonomy_default_vocabularies() {
  return array(
    'insurance_certificates' => array(
      'name' => 'Insurance Certs',
      'machine_name' => 'insurance_certificates',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
