@S = window.S ? {}

class S.BuildingPlanEditor
	constructor: (@Lmap) ->
		# Initialize the FeatureGroup to store editable layers
		@drawnItems = new L.FeatureGroup()
		@Lmap.addLayer @drawnItems

		# Initialize the draw control and pass it the FeatureGroup of editable layers
		@drawControl = new L.Control.Draw(edit:
			featureGroup: @drawnItems
		)
		@Lmap.addControl @drawControl




		@rectangle = null
		ne = new L.LatLng(60.17919912560938, 24.79567587375641)
		sw = new L.LatLng(60.178396148360065, 24.792988300323486)
		@rectangle = new L.Rectangle(new L.LatLngBounds(sw, ne))
		@drawnItems.addLayer @rectangle

		#generate dummy floor plan
		angle = $(".tfAngle").val()
		opacity = $(".tfOpacity").val()
		saveScale = $(".tfSaveScale").is(":checked")


		@buildingPlan = new S.BuildingPlanLayer  @rectangle.getBounds(), angle, saveScale, opacity: opacity
		@buildingPlan.setFloorLayer 0, "res/floor1.png"
		@buildingPlan.setFloorLayer 1, "res/floor2.png"
		@buildingPlan.setFloorLayer 2, ""
		@buildingPlan.setFloorLayer 3, ""

		@buildingPlan.addTo @Lmap

		@buildingPlan.setCurrentFloorIndex 0


		#update floor plan
		@updateFloorPlan()

		#respond to draw event's to update floorplan corrspondingly
		@Lmap.on "draw:created", (e) =>
			type = e.layerType
			layer = e.layer
			if type is "rectangle"
				unless @rectangle
					@rectangle = e.layer
					@drawnItems.addLayer layer

			else if type is "marker"
				layer= new S.StationMarker(layer) # transformating a marker to a station marker
				layer.setName "NewMarker"
				layer.setFloorNumber parseInt $(".tfFloorNumber").val()

				@buildingPlan.addMarker layer

			#to edit markers
			@drawnItems.addLayer layer
			#fit the floormap in the drawn bounds
			@updateFloorPlan()

		@Lmap.on "draw:edited", (e) =>
			type = e.layerType
			layer = e.layer

			#fit the floormap in the drawn bounds
			@updateFloorPlan()

		@Lmap.on "draw:drawstart", (e) =>
			type = e.layerType

		$(".tfImageUrl").bind "input", (e) =>
			url =  $(".tfImageUrl").val()
			floorNumber = parseInt $(".tfFloorNumber").val()
			console.log 'updating floor imaqge'
			@buildingPlan.setFloorLayer floorNumber, url


		#add dummy marker
		marker = new L.Marker new L.LatLng( 60.178542873243664,24.793814420700073);
		#marker.addTo(map);
		@Lmap.fireEvent 'draw:created', { layer:marker, layerType: "marker" }

	loadStationsFromJSON:(jsonString) ->
		@buildingPlan.loadStationsFromJSON jsonString

	updateStationsJSON: ->
		$(".tfAllJSON").val (@buildingPlan.getStationsJSON())

	updateFloorPlan: =>
		if @rectangle
			#@Lmap.removeLayer @buildingPlan  if @buildingPlan


			angle = $(".tfAngle").val()
			opacity = $(".tfOpacity").val()
			saveScale = $(".tfSaveScale").is(":checked")
			@buildingPlan.setParams @rectangle.getBounds(), angle, saveScale, opacity: opacity

			url =  $(".tfImageUrl").val()
			floorNumber = parseInt $(".tfFloorNumber").val()
			@buildingPlan.setCurrentFloorIndex floorNumber

			console.log "image url is #{@buildingPlan.floors[@buildingPlan.currentFloorIndex]._url}"
			$(".tfImageUrl").val @buildingPlan.floors[@buildingPlan.currentFloorIndex]._url


			#@buildingPlan.setFloorLayer floorNumber, url

			# floorPlan.setOpacity( $(".tfOpacity").val() );
			#@buildingPlan.addTo @Lmap

			#crack to TODO get rid of it


		#update output info
		@updateStationsJSON()

		$(".tfSWLat").val @rectangle.getBounds().getSouthWest().lat
		$(".tfSWLng").val @rectangle.getBounds().getSouthWest().lng
		$(".tfNELat").val @rectangle.getBounds().getNorthEast().lat
		$(".tfNELng").val @rectangle.getBounds().getNorthEast().lng

	@buildingPlan : null

	@drawnItems : null