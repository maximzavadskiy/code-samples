@S = window.S ? {}

class S.BuildingPlanLayer extends L.LayerGroup
	constructor: ( @bounds, @rotation=0, @saveProportions=false, @S_options={}) ->
		super()

	## called when added to map
	onAdd: (aLmap) ->
		super(aLmap)

		@oms = new OverlappingMarkerSpiderfier aLmap, this, legWeight: 5, keepSpiderfied: true, nearbyDistance: 50
		aLmap.removeEventListener e  for e in ['click' , 'zoomend']
		aLmap.addEventListener 'zoomend', => @updateOverlappingMarkers()

		#@oms.legWeight = 50
		@oms.legColors.usual = '#000'


	updateOverlappingMarkers: ->
		console.log "updateOverlappingMarkers"

		#@oms?.unspiderfy()
		@oms?.clearMarkers()

		for marker in @markers
			#@oms.unspiderfy marker
			if marker.getFloorNumber() is @currentFloorIndex
				@oms.addMarker marker
				#@oms.spiderListener marker if not marker._omsData #don't double spiderfy

		@oms?.spiderAll()

	loadStationsFromJSON: (jsonString) ->
		#console.log "Stations loading from #{jsonString}"
		markersJSONArray = JSON.parse(jsonString)

		for markerJSON in markersJSONArray
			marker = new S.StationMarker()
			@addMarker marker
			marker.loadFromJSON JSON.stringify(markerJSON), @floors[0]

	openTagPopupById: (tagId) ->
		for tag in @markers
			if parseInt(tag.getTagId?()) is tagId # ? to filter tags from other markers
				console.log "opening tag #{tagId}"

				@setCurrentFloorIndex tag.getFloorNumber()
				#setInterval(tag.openPopup, 5) # show clicked tag on the map
				tag.openPopup()


	addMarker: (markerLayer) ->
		markerLayer.addEventListener 'beforeMove', => @oms.unspiderfy() ## to save real location, oms doesn not support moving

		@markers.push markerLayer

		@addLayer markerLayer

		## add it to spiderfy plugin to manage overlaying markers
		#@oms.addMarker markerLayer

		@updateMarkerVisibility()

	removeMarker: (markerLayer) ->
		@removeLayer markerLayer

		@markers = jQuery.grep @markers, (marker) ->
			marker != markerLayer

		@updateMarkerVisibility()

	setParams:  ( @bounds, @rotation=0, @saveProportions=false, @S_options={}) ->
		@_updateFloor i  for floor, i in @floors

	setFloorLayer: (floorNo, imageUrl) ->
		newFloor = new FloorPlanLayer imageUrl, @bounds, @rotation, @saveProportions, @S_options

		if @floors[floorNo] then @removeLayer @floors[floorNo] # remove previous if there was

		#@addLayer newFloor
		@floors[floorNo] = newFloor

		@setCurrentFloorIndex floorNo

	setCurrentFloorIndex: (index) ->
		return if isNaN(index)

		oldFloorInd = @currentFloorIndex
		@currentFloorIndex = index

		@updateMarkerVisibility()
		#remove other floors from a map
		#@removeLayer floor for floor in @floors

		@removeLayer @floors[oldFloorInd]

		#add this floor to the map
		@addLayer @floors[@currentFloorIndex]


		#done with reordering layers -> update other stuff to be in front

	updateMarkerVisibility: ->
		for marker in @markers
			if marker.getFloorNumber() is @currentFloorIndex
				@addLayer marker
			else
				@removeLayer marker

		@updateOverlappingMarkers()

	getStationsJSON: ->
		stationsJSON = new Array()
		stationsJSON.push marker.getJSONObject() for marker in @markers
		return JSON.stringify stationsJSON


	_updateFloor: (floorNum) ->
		#floor = new FloorPlanLayer floor.getUrl(), @bounds, @rotation, @saveProportions, @options
		@setFloorLayer floorNum, @floors[floorNum].getUrl()

	floors: [] # array of floors
	markers:[]
	currentFloorIndex: 0
	oms: null