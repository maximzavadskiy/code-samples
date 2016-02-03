@S = window.S ? {}

class S.StationMarker extends L.Marker
	constructor: (lMarkerOrLatLng) ->
		if lMarkerOrLatLng instanceof L.Marker
			jQuery.extend( true, this, lMarkerOrLatLng ) # deep copy of the argument to self
		else if lMarkerOrLatLng
			super lMarkerOrLatLng
		else ##no args
			console.log "no agrs"
			super new L.LatLng 0,0

		@on "click", ->
			#!TODO popup is crated again each time it's clicked, optimize this
			popupContent = document.createElement('a')
			$(popupContent).html " <b> Lat: </b>  #{@getLat()} <br> <b>Lng: </b>  #{@getLng()} <br> " +
									" <b> Name: </b> <input type='text' class='name' value= '#{@getName()}'/> <br>" +
									" <b> ID: </b> <input type='text' class='id' value= '#{@getID()}'/> <br>" +
									"<b> Floor: </b> <input type='text' class='floor' value= '#{@getFloorNumber()}'/> <br> " +
								 	" <b> JSON: </b> <input type='text' readonly='true' class='json' value= '#{@toJSON()}'/> <br>" +
									" <input type='button' class='ok' value='Save&Close'> "
			#!TODO Save on close popup
			$(popupContent).find(".ok").click =>
				@setPropertiesFromForm popupContent, '.name', '.id', '.floor'
				@closePopup()

			#auto save on field's content change and update json
			$(popupContent).find("input").bind  "input", (e) =>
				@setPropertiesFromForm popupContent, '.name', '.id', '.floor'
				$(popupContent).find(".json").val @toJSON()

			@bindPopup	popupContent

	#floorPlanLayer is used to construct using relative coords
	loadFromJSON: (jsonString, floorPlanLayer) ->

		console.log "loading marker from #{jsonString}"
		markerJSON= JSON.parse jsonString

		@name= 	markerJSON.name
		@id= 	markerJSON.id
		@floorNumber =  parseInt markerJSON.position.floor # in case it might be string
		console.log "floor number: #{@floorNumber}"

		if markerJSON.position.gpsCoordinates
			@setLatLng new L.LatLng markerJSON.position.gpsCoordinates.latitude, markerJSON.position.gpsCoordinates.longitude
		else
			propX= markerJSON.position.proportionX
			propY= markerJSON.position.proportionY

			@setLatLng floorPlanLayer.convertProportionPositionToLatLng( x:propX, y:propY)

	#!TODO study protecting private properties
	getFloorNumber: ->
		@floorNumber

	setFloorNumber: (num)->
		if isNaN num
			console.log "ERROR in setFlooNumber - #{num} is not a number"
			return
		@floorNumber= num

	setName: (@name) ->
	getName: ->
		@name

	setID: (@id) ->
	getID: ->
		@id

	getJSONObject: ->
		id: @id
		name: @name
		position:
			gpsCoordinates:
				latitude: @getLat()
				longitude: @getLng()
			floor: @floorNumber

	toJSON: ->
		JSON.stringify @getJSONObject()

	setPropertiesFromForm: (htmlForm, nameSelector, idSelector, floorSelector) ->
		@name= 	$(htmlForm).find(nameSelector).val()
		@id= 	$(htmlForm).find(idSelector).val()
		@floorNumber =  parseInt $(htmlForm).find(floorSelector).val()


	getLat: ->
		@getLatLng().lat

	getLng: ->
		@getLatLng().lng

	id: ""
	name: ""
	floorNumber: 0