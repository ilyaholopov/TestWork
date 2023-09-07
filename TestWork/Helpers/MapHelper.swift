//
//  MapHelper.swift
//  TestWork
//
//  Created by Илья Холопов on 07.09.2023.
//

import Foundation
import GLMap

class MapHelper: NSObject {
    
    var map: GLMapView
    weak var parrentView: UIView?
    var mapImageUser = GLMapImage(drawOrder: 3)
    var myLocationImage = GLMapImage(drawOrder: 3)
    
    var locationManager: CLLocationManager!
    var userList: [User] = []
    
    init(parentView: UIView) {
        GLMapManager.shared.tileDownloadingAllowed = true
        
        self.parrentView = parentView
        
        map = GLMapView(frame: self.parrentView!.bounds)
        self.parrentView!.addSubview(map)
        self.parrentView!.sendSubviewToBack(map)
        
        map.mapZoomLevel = 15
    }
    
    deinit {
        locationManager?.stopUpdatingLocation()
    }
    
    public func setupCurrentLocation() {
        locationManager = CLLocationManager()
        locationManager.delegate = self
        locationManager.requestAlwaysAuthorization()
        
        locationManager.startUpdatingLocation()
        
        showCurrentLocation()
    }
    
    public func showCurrentLocation() {
        guard let lat = locationManager?.location?.coordinate.latitude, let long = locationManager?.location?.coordinate.longitude else { return }
        map.mapCenter = GLMapPoint(lat: lat, lon: long)
        map.mapZoomLevel = 15
        map.mapAngle = 0.0
    }
    
    public func addUserMap(userList: [User]) {
        guard let image = UIImage(named: "ic_tracker_75dp"), let defualtImage = (UIImage(systemName: "person.circle.fill")?.withTintColor(.white, renderingMode: .alwaysOriginal)) else { return }
        
        userList.forEach { user in
            var avatar = UIImage()
            if user.avatarImage != nil {
                if let image = UIImage(named: user.avatarImage!)?.cropImageToCircle() {
                    avatar = image
                } else {
                    avatar = defualtImage
                }
            } else {
                avatar = defualtImage
            }
            let avatarImage = UIImage.imageByMergingImages(topImage: avatar, bottomImage: image, scaleForTop: 2.0)
            
            let mapImage = GLMapImage(drawOrder: 3)
            mapImage.setImage(avatarImage, for: map)
            mapImage.offset = CGPoint(x: image.size.width / 2, y: 0)
            mapImage.position = GLMapPoint(lat: user.coordinate?.lat ?? 0.0, lon: user.coordinate?.lon ?? 0.0)
            map.add(mapImage)
        }
    }
    
    public func showUser(user: User) {
        map.mapCenter = GLMapPoint(lat: user.coordinate?.lat ?? 0.0, lon: user.coordinate?.lon ?? 0.0)
        map.mapZoomLevel = 16
    }
    
    public func plusZoom() {
        map.mapZoomLevel = map.mapZoomLevel + 1
    }
    
    public func minusZoom() {
        map.mapZoomLevel = map.mapZoomLevel - 1
    }
    
    private func updateUserLocation(latitude: CLLocationDegrees, longitude: CLLocationDegrees) {
        let userGeoLocation = GLMapGeoPoint(lat: latitude, lon: longitude)
        let userLocation = GLMapPoint(geoPoint: userGeoLocation)
        
        guard let image = UIImage(named: "ic_mylocation_55dp") else { return }
        
        myLocationImage.setImage(image, for: map)
        myLocationImage.offset = CGPoint(x: image.size.width / 2, y: 0)
        myLocationImage.position = userLocation
        
        map.add(myLocationImage)
    }
}

extension MapHelper: CLLocationManagerDelegate {
    func locationManager(_ manager: CLLocationManager, didUpdateLocations locations: [CLLocation]) {
        if let location = locations.last {
            let latitude = location.coordinate.latitude
            let longitude = location.coordinate.longitude
            
            updateUserLocation(latitude: latitude, longitude: longitude)
        }
    }
}
