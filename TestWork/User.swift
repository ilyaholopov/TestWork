//
//  User.swift
//  TestWork
//
//  Created by Илья Холопов on 07.09.2023.
//

import Foundation
import UIKit

struct User: Equatable {
    static func == (lhs: User, rhs: User) -> Bool {
        return lhs.name == rhs.name
    }
    
    var name: String?
    var date: Date?
    var avatarImage: String?
    var coordinate: (lat: Double, lon: Double)?
    
    init() { }
    
    init(name: String, date: Date?, avatar: String?, latitude: Double, longitude: Double) {
        self.name = name
        self.date = date
        self.avatarImage = avatar
        self.coordinate = (latitude, longitude)
    }
}
