if Meteor.isClient
	Meteor.subscribe 'all-batches'

	Session.setDefault 'admin-is-edit-batch-page', false # repeating functionality as with batchs - make an utility
	Session.setDefault 'admin-is-saving-batch', false
	Session.setDefault 'admin-batch-edit-id', null
	Session.setDefault 'admin-batch-products-by-lifetime', null

	BatchProductsByLifetime = new Meteor.Collection null #local collection to store product listings, dynamically created by user

	batchImagePlaceholderURL = '/batchImagePlaceholder.jpg'
	
	Template.admin_batches.helpers 
	
		currentBatch :  ->
			console.log getCurrentBatch()
			getCurrentBatch()

		selectedIfTime : (productionTimeH) ->
			if @productionTime?.h is parseInt productionTimeH
				'selected' 
			else
				 ''

		checkedIfDay : (day) ->
			 if @productionDays and day in @productionDays
			 	'checked' 
			 else
			 	''

		equal : (a, b)->
			return a is b


		batchProductsWithLifetime : (lifetimeHours) ->
			Template.main.util_BatchProductsWithLifetimeForBatchId  BatchProductsByLifetime, lifetimeHours, getCurrentBatch if getCurrentBatch() isnt {} 

		isCreatingNew : ->
			return  Session.equals 'admin-batch-edit-id', null

		isEditPage : ->
			return (Session.get 'admin-is-edit-batch-page') or (Session.get 'admin-batch-edit-id')

		isSavingBatch : ->
			return Session.get 'admin-is-saving-batch'

	Template.admin_batches.events =
		'click .btn-delete' : ->
			bootbox.confirm 'Möchten Sie der Batch wirklich löschen?', (result) =>
				Batches.remove { _id: @_id } if result
	# TODO replace with modal windows

		'click .btn-edit' : ->
			Session.set 'admin-batch-edit-id', @_id

		'click #btn-goto-create-new-batch' : ->
			Session.set 'admin-is-edit-batch-page', true

		'click .btn-add'  : (event, template) ->
			BatchProductsByLifetime.insert {lifetimeHours: @lifetimeHours}
			# # TODO get rid of this, its a shame. Simulates change event, so product id is updated for batch
			# $(template.findAll ".product-name" ).trigger 'change'

		'click .btn-exclude' : ->
			BatchProductsByLifetime.remove {_id: @_id}

		# TODO optimize, no need to update every time, can fetch once, when saving
		'input .edit-batch-product-amount ' : (event) ->
			BatchProductsByLifetime.update {_id: @_id}, $set : {productAmount: parseInt $(event.currentTarget).val() }
		
		'change .admin-batch-edit-product-name ' : (event) ->
			BatchProductsByLifetime.update {_id: @_id}, $set : { productId: $(event.currentTarget).val() }

		'click #btn-cancel-edit' : ->
			gotoListPage()

		'click #btn-save' : (event, template) -> #saves new, or updates if one is edited
			isEditingExisting = Session.get 'admin-batch-edit-id'

			newBatch =
				productionTime:
					h: parseInt $( template.find '#input-production-time' ).val() #save lifetime in minutes
				productionDays: $(day).val() for day in template.findAll "#input-weekdays input:checkbox:checked"
				name: template.find("#input-batch-name").value
				products: BatchProductsByLifetime.find( productId: {$exists : true}, productAmount: {$gt : 0}).map (elem) -> 
					id: elem.productId
					amount: elem.productAmount


			 # createdAt field should be only added when creating, not when editing
			if not isEditingExisting then newBatch.createdAt =  new Date  
			
			#log.info 'batch to save/update:', newBatch

			onResult = (err, result) -> ##callback
					Session.set 'admin-is-saving-batch', false

					if not err
						gotoListPage()
						bootbox.alert 'Der Batch gespeichert' #TODO translate/replace
					else
						log.error 'Error while saving batch', {error: err, batch: newBatch}
						bootbox.alert 'Failed to save batch. Please copy the following error message and show to Max. Then try again. Error: #{err}'

			Session.set 'admin-is-saving-batch', true

			if isEditingExisting
				Batches.update { _id : Session.get 'admin-batch-edit-id'}, { $set : newBatch }, {}, onResult
			else
				Batches.insert newBatch, onResult

	gotoListPage = ->
		#clear session vars
		Session.set 'admin-is-edit-batch-page', false
		if Session.get 'admin-batch-edit-id'
			Session.set 'admin-batch-edit-id', null
		BatchProductsByLifetime.remove {}

	getCurrentBatch = ->
		if Session.get 'admin-batch-edit-id'
			Batches.findOne { _id : Session.get 'admin-batch-edit-id' } 
		else
			{}