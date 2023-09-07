//
//  ViewController.swift
//  TestWork
//
//  Created by Илья Холопов on 07.09.2023.
//

import UIKit
import GLMap
import CoreLocation

class ViewController: UIViewController {
    
    var userList: [User] = [
        User(name: "Ilya", date: Date(), avatar: "user1", latitude: 59.88845, longitude: 30.39645),
        User(name: "Ivan", date: Date(), avatar: "user2", latitude: 59.95145, longitude: 30.38428),
        User(name: "Dima", date: Date(), avatar: "user3", latitude: 59.90417, longitude: 30.29532),
        User(name: "Misha", date: Date(), avatar: nil, latitude: 60.01322, longitude: 30.29857)
    ]

    @IBOutlet weak var plusZoomButton: UIButton!
    @IBOutlet weak var minusZoomButton: UIButton!
    
    var currentSelectUser = 0
    let lock = NSRecursiveLock()
    
    var bottomVC: BottomViewViewController!
    
    var mapHelper: MapHelper!
    
    @IBAction func plusZoomButt(_ sender: UIButton) {
        mapHelper.plusZoom()
    }
    
    @IBAction func minusZoomButt(_ sender: UIButton) {
        mapHelper.minusZoom()
    }
    
    @IBAction func showMyLocation(_ sender: UIButton) {
        mapHelper.showCurrentLocation()
        showBottomVC(status: false)
    }
    
    @IBAction func showUserButt(_ sender: UIButton) {
        mapHelper.showUser(user: userList[currentSelectUser])
        self.bottomVC.updateUser(selectUser: userList[currentSelectUser])
        if currentSelectUser < (userList.count - 1) {
            currentSelectUser += 1
        } else {
            currentSelectUser = 0
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        mapHelper = MapHelper(parentView: self.view)
        mapHelper.setupCurrentLocation()
        
        mapHelper.map.tapGestureBlock = { [weak self] (point: CGPoint) in
            guard let self = self else { return }
            if let userSelect = findUser(point: point, mapView: mapHelper.map) {
                self.bottomVC.updateUser(selectUser: userSelect)
                mapHelper.showUser(user: userSelect)
                showBottomVC(status: true)
            }
            
        }
        
        bottomVC = BottomViewViewController()
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
        mapHelper.addUserMap(userList: userList)
        addChildVC()
    }
    
    func addChildVC() {
        addChild(bottomVC)
        self.view.addSubview(bottomVC.view)
        bottomVC.view.frame = CGRect(x: 0.0, y: self.view.frame.maxY, width: self.view.frame.width, height: 150.0)
        self.didMove(toParent: self)
    }
    
    private func showBottomVC(status: Bool) {
        UIView.animate(withDuration: 0.3) {
            self.bottomVC.view.frame = CGRect(x: 0.0,
                                              y: status ? self.view.frame.maxY - 150 : self.view.frame.maxY,
                                              width: self.view.frame.width, height: 150.0)
        }
    }
    
    private func findUser(point: CGPoint, mapView: GLMapView) -> User? {
        var userSelect: User?
        lock.lock()

        let rect = CGRect(x: -30, y: +20, width: 60, height: 60).offsetBy(dx: point.x, dy: point.y)
        
        userList.forEach { user in
            if rect.contains(mapView.makeDisplayPoint(from: GLMapPoint(lat: user.coordinate?.lat ?? 0.0, lon: user.coordinate?.lon ?? 0.0))) {
                userSelect = user
            }
        }
        lock.unlock()
        return userSelect
    }
}

