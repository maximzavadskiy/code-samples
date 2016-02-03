if Meteor.isClient
	BatchProductsByLifetime = new Meteor.Collection null #local collection to store product listings, dynamically created by user

	Session.setDefault 'bistro-produce-batch-id', null # repeating functionality as with batchs - make an utility

	Session.set 'bistro-produce-batch-total', 0

	Template.bistro_produce_batch.helpers
	
		isAdjustPage : ->
			'string' is typeof Session.get 'bistro-produce-batch-id'

		batchProductsWithLifetime : (lifetimeHours) -> 
			recalcTotalAmount() #on page load update total amount
			Template.main.util_BatchProductsWithLifetimeForBatchId BatchProductsByLifetime, lifetimeHours, getCurrentBatch, true

		totalProducts : (template) ->
			total = Session.get 'bistro-produce-batch-total'
			# BatchProductsByLifetime.find(isIncluded: {$ne: false}).forEach (prodItem) ->
			# 	total += prodItem.productAmount
			return total

		productDisabled : ->
			return  @isIncluded is false

		batchName :  ->
			return getCurrentBatch()?.name

		batchProduceHour : ->
			return getCurrentBatch()?.productionTime.h

		batchProduceDaysStr : ->
			daysArr = getCurrentBatch()?.productionDays or []

			dayIds = Template.main.weekDayIds()
			dayNames = Template.main.weekDayNamesShort()
			monToFriIds =  dayIds.slice(0,5)

			prevDayId = ""
			rangeLength = 0
			produceDaysStr = ""

			stillMatchDays = true
			for batchDayId in daysArr 
				if monToFriIds.indexOf(batchDayId) < 0
					stillMatchDays = false

			if stillMatchDays
				return "#{dayNames[0]}-#{dayNames[4]}"
			else
				return (dayNames[dayIds.indexOf day] for day in daysArr).join ', '
		

	Template.bistro_produce_batch.events =
		'click #btn-back-to-bistro' : ->
			gotoBistro()

		'click #btn-back-to-batch-select' : ->
			#remove all batch products from the cache, so other batch can use it
			BatchProductsByLifetime.remove {}
			Session.set 'bistro-produce-batch-id', null

		'click .batch-item' : ->
			log.info "Selected to produce batch #{@_id}"
			Session.set 'bistro-produce-batch-id', @_id

		'click #btn-produce' : (evt, template)->
			batchId = Session.get 'bistro-produce-batch-id'
			log.info "Producing batch #{batchId} ..."

			totalToBeProduced = 0
			#get all divs containing batch's products info from html
			productDoms = template.findAll '.product-controls'
			
			insertPromises = []

			products = for productDom in productDoms
				#produce checked products
				if $(productDom).find('.chbx-product-include').is(':checked')
					productAmount = parseInt($(productDom).find('.edit-batch-product-amount').val()) or 0
					if productAmount < 0 then productAmount = 0

					log.info "...Producing #{productAmount} of #{$(productDom).prop("id")}"


					for  [0...productAmount]
						promise = new Promise (resolve, reject) ->
							ProductLogs.insert {
							#TODO common method to insert logs (inserts date, etc.)
								productId : $(productDom).prop("id")
								producedAt: new Date
								status : 'produced'
							}, (err,res) ->
								console.log "data inserted"
								resolve res

								if err
									reject err
									log.error "bistro_produce_batch: Could not insert ProductLogs for {elem.productId}, error message", err
					
						insertPromises.push promise

					totalToBeProduced += productAmount

					res =
						productId : $(productDom).prop("id")
						amount : productAmount
						
			# Produce all logs from promises
			batch = Batches.findOne _id : batchId
			BistroEvents.insert 
				timestamp: new Date
				type: 'produce' #TODO or keep 'insert' and use bistroType extra field?
				subject:
					collectionName: 'Batch'
					document: batch
				#TODO save result amount, product logs and etc.

			Promise.all(insertPromises).then ->
				log.info 'All produce batch data succesfully saved in the database'
			, ->
				bootbox.alert "ERROR. There was an error while saving to database. Please notify the administrator."


			log.info "Producing completed. Total produced #{totalToBeProduced}"

			gotoBistro()

		'change .chbx-product-include'  : (event, template) ->
			recalcTotalAmount()

		'click .product-name' : (event, template) ->
			chckbx =  $(event.currentTarget).parent().find('.chbx-product-include')
			chckbx.prop "checked", not chckbx.is(":checked")
			recalcTotalAmount()

		'input .edit-batch-product-amount, focus .edit-batch-product-amount' : (event) ->
			recalcTotalAmount()

		'click .btn-inc' : (event) ->
			onStepAmountClick event, +1, @_id

		'click .btn-dec' : (event) ->
			onStepAmountClick event, -1, @_id

	onStepAmountClick = (event, step, _id) ->
		event.preventDefault()
		input = $(event.currentTarget).parent().find("input")
		input.val parseInt(input.val()) + parseInt(step)
		recalcTotalAmount()
		# Session.set 'bistro-produce-batch-total', Session.get('bistro-produce-batch-total')+step

	gotoBistro = ->
		#remove all batch products from the cache, so other batch can use it
		#TODO WARNING not good way, need to automatically clean it when new batch is selected
		BatchProductsByLifetime.remove {}
		Session.set 'bistro-produce-batch-id', null #reset selected batch, so next time it will be again in batch selection screen
		Router.go 'bistro_vitrine'

	getCurrentBatch = ->
		Batches.findOne { _id : Session.get 'bistro-produce-batch-id' } if Session.get 'bistro-produce-batch-id'

	forEachEnabledProductNode = (template, onEach)->
		productDoms = $.find '.batch-product-entries'

		for productDom in productDoms
			#produce checked products
			if $(productDom).find('.chbx-product-include').is(':checked')
				productAmount = parseInt($(productDom).find('.edit-batch-product-amount').val()) or 0
				onEach productDom, productAmount

	recalcTotalAmount = ->
		totalProduced = 0
			#get all divs containing batch's products info from html
		productDoms = $("div.bistro").find '.product-controls'
		totalProduced = 0

		for productDom in productDoms
			#produce checked products
			if $(productDom).find('.chbx-product-include').is(':checked')
				productAmount = parseInt($(productDom).find('.edit-batch-product-amount').val()) or 0
				if productAmount < 0 then productAmount = 0
				totalProduced += productAmount

		Session.set 'bistro-produce-batch-total', totalProduced


